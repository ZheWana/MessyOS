#include "main.h"
#include "fm33le0xx_fl.h"
#include "uart0_DMAtx.h"

#include "messyos.h"
int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();

    /* Configure the system clock */
    /* SHOULD BE KEPT!!! */
    MF_SystemClock_Config();

    /* Initialize FL Driver Library */
    /* SHOULD BE KEPT!!! */
    FL_Init();

    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
    MF_Config_Init();

    DMA_Uart0_TX();

    
    while (1) {
    }
}
