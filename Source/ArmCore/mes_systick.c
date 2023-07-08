/**
 * @file mes_systick.c
 * @author ZheWana (zhewana@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "mes_systick.h"
#include "mes_sys.h"

typedef struct SysTickTypdef {
    volatile uint32_t CTRL;
    volatile uint32_t RELOAD;
    volatile uint32_t VALUE;
    volatile uint32_t CALIB;
} SysTickTypdef;

SysTickTypdef* SysTick = (SysTickTypdef*)0xE000E010;

void SystickInit(void)
{
    // 设置重载值
    SysTick->RELOAD = SYSTICKFREQ / 100;
    // 当前值归零
    SysTick->VALUE = SysTick->RELOAD;
    // 开启中断 使能定时器
    SysTick->CTRL |= 0x7;
}