/**
 * @file sys.h
 * @author ZheWana (zhewana@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-07-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __MES_SYS_H
#define __MES_SYS_H
#include "stdint.h"

#define disable_irq() __asm__("cpsid i")
#define enable_irq() __asm__("cpsie i")

void PendSVInit(void);

void CallPendSV(void);

#endif // !__MES_SYS_H
