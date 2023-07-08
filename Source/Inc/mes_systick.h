/**
 * @file mes_systick.h
 * @author ZheWana (zhewana@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-07-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __MES_SYSTICK_H
#define __MES_SYSTICK_H

#include "stdint.h"

#define SYSTICKFREQ 12000000

void SystickInit(void);

void SysTick_Handler(void);

#endif // !__MES_SYSTICK_H
