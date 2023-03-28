/**
 * @file sys.c
 * @author ZheWana (zhewana@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-07-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "mes_sys.h"

typedef struct SCBTypedef {
    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint32_t SHPR1;
    volatile uint32_t SHPR2;
    volatile uint32_t SHPR3;
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    volatile uint32_t DFSR;
    volatile uint32_t MMFAR;
    volatile uint32_t BFAR;
    volatile uint32_t AFSR;
} SCBTypedef;

SCBTypedef* SCB = ((SCBTypedef*)0xE000ED00);

void PendSVInit(void)
{
    // 设置PendSV优先级
    SCB->SHPR3 = 0xFF << 16;
}

void CallPendSV(void)
{
    SCB->ICSR |= 1 << 28;
}
