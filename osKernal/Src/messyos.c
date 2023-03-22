/**
 * @file messyos.c
 * @author ZheWana (zhewana@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-07-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "messyos.h"
#include "mes_sys.h"
#include "mes_systick.h"

#include "stdlib.h"

static struct MessyOS {
    mosTask_t* taskListHead; // 任务链表头
    mosTask_t* taskListTail; // 任务链表尾
    mosTask_t* RdyListHead; // 任务就绪链表头
    mosTask_t* RdyListTail; // 任务就绪链表尾
    mosTask_t* RunningTask; // 运行任务指针

    uint8_t isKernalOK : 1;
} MessyOS;

uint8_t IsOSReady(void)
{
    return MessyOS.isKernalOK;
}

//---------------------  MessyOS Kernal Functions  --------------------//

extern void MOS_SetSP(uint32_t);

void MOS_osStart(void)
{
    PendSVInit();
    SystickInit();
    MessyOS.isKernalOK = 1;
}

MOS_Status MOS_AddToRdyList(mosTask_t* pTask)
{
    if (MessyOS.RdyListHead == NULL) {
        MessyOS.RdyListHead = pTask;
        MessyOS.RdyListTail = pTask;
    } else {
        mosTask_t* mark = NULL; // 记录插入位置
        for (mosTask_t* index = MessyOS.RdyListTail; index != NULL; index = index->last) {
            if (index == pTask) {
                return MOS_Error;
            } else {
                if (index->priority < pTask->priority && mark == NULL) {
                    mark = index;
                }
            }
        }

        // 测试用
        mark = MessyOS.RdyListTail;

        if (mark == NULL) {
            pTask->next = MessyOS.RdyListHead;
            pTask->last = NULL;
            MessyOS.RdyListHead = pTask;
        } else {

            if (MessyOS.RdyListTail == mark) {
                MessyOS.RdyListTail->next = pTask;
                MessyOS.RdyListTail = pTask;
                pTask->last = NULL;
            } else {
                pTask->next = mark->next;
                mark->next->last = pTask;

                mark->next = pTask;
                pTask->last = mark;
            }
        }
    }
    return MOS_OK;
}

MOS_Status MOS_CreatTask(mosTask_t* pTask, uint32_t stackLen, uint8_t taskPriority, MOS_TaskState curState, Func_t taskHandler)
{
    disable_irq();

    // 初始化任务句柄
    // if (MessyOS.taskListHead == NULL) {
    //     pTask->last = NULL;
    //     pTask->next = NULL;
    //     MessyOS.taskListHead = pTask;
    //     MessyOS.taskListTail = pTask;
    // } else {
    //     MessyOS.taskListTail->next = pTask;
    //     pTask->last = MessyOS.taskListTail;
    //     MessyOS.taskListTail = pTask;
    // }

    pTask->priority = taskPriority;
    pTask->state = curState;

    // 创建任务栈，存储与任务句柄中
    pTask->curSP = (uint32_t)malloc(sizeof(char) * stackLen);
    if ((void*)pTask->curSP == NULL) {
        return MOS_Error;
    }
    uint32_t* stackTop = (uint32_t*)(pTask->curSP + stackLen - 4);
    stackTop -= 15;

    // 伪造软件保存的栈：R4~R11
    for (int i = 0; i < 8; i++) {
        stackTop[i] = 0; // R(i+4)
    }

    // 伪造硬件保存的栈：
    for (int i = 8; i < 12; i++) {
        stackTop[i] = 0; // Ri
    }

    stackTop[12] = 0; // R12
    stackTop[13] = 0; // LR
    stackTop[14] = (uint32_t)taskHandler; // 返回地址
    stackTop[15] = 1 << 24; // xPSR.T = 1 => Thumb Set

    pTask->curSP = (uint32_t)stackTop;

    // 修改就绪链表
    if (pTask->state == MOS_TaskReady) {
        MOS_Status res = MOS_AddToRdyList(pTask);
        if (res != MOS_OK) {
            free((void*)pTask->curSP);
            pTask->curSP = 0;
        }
    }

    enable_irq();

    return MOS_OK;
}

uint32_t MOS_TaskScheduling(uint32_t sp)
{
    uint32_t saveFlag = 0;

    if (MessyOS.RdyListHead == NULL)
        return MOS_OK;

    if (MessyOS.RunningTask != NULL) { // 任务切换
        // if (MessyOS.RdyListHead->priority > MessyOS.RunningTask->priority) {
        // 软件保存上个任务现场
        saveFlag = 1;

        // 更新任务栈指针
        MessyOS.RunningTask->curSP = sp - 32;

        // 当前任务变为就绪态
        MessyOS.RunningTask->state = MOS_TaskReady;
        MOS_AddToRdyList(MessyOS.RunningTask);
        // } else {
        //     return MOS_OK;
        // }
    }

    // 当前任务指针修改为就绪链表首个任务
    MessyOS.RunningTask = MessyOS.RdyListHead;

    // 当前任务变为运行态
    MessyOS.RunningTask->state = MOS_TaskRunning;

    // 删除就绪链表首个任务
    if (MessyOS.RdyListTail == MessyOS.RunningTask) {
        MessyOS.RdyListTail = NULL;
    }
    MessyOS.RdyListHead = MessyOS.RdyListHead->next;
    MessyOS.RdyListHead->last = NULL;

    return MessyOS.RunningTask->curSP + saveFlag;
}

//---------------------  System Handler  --------------------//

void SysTick_Handler(void)
{
    CallPendSV();
}
