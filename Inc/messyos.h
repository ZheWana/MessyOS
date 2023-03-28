/**
 * @file messyos.h
 * @author ZheWana (zhewana@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-07-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __MESSYOS_H
#define __MESSYOS_H

#include "stdint.h"

typedef enum MOS_Status {
    MOS_OK = 0,
    MOS_Error = 1,

} MOS_Status;

typedef enum MOS_TaskState {
    MOS_TaskReady = 0,
    MOS_TaskRunning,
    MOS_TaskBlockes,
    MOS_TaskTerninated,
} MOS_TaskState;

typedef struct mosTask_t {
    struct mosTask_t* last;
    struct mosTask_t* next;

    MOS_TaskState state;

    uint8_t priority;

    uint32_t curSP;
} mosTask_t, *pmosTask_t;

typedef void (*Func_t)(void);

uint8_t IsOSReady(void);

void MOS_osStart(void);

MOS_Status MOS_CreatTask(mosTask_t* pTask, uint32_t stackLen, uint8_t taskPriority, MOS_TaskState curState, Func_t taskHandler);

#endif // !__MESSYOS_H
