#include "main.h"

#include "uart0_DMAtx.h"

uint8_t CHANNEL_2_TransferComplete = 0;

void DMA_IRQHandler(void)
{
    //DMA中断处理
    if((FL_ENABLE == FL_DMA_IsEnabledIT_TransferComplete(DMA, FL_DMA_CHANNEL_2))
            && (FL_SET == FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_2)))
    {
        FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_2);  //清DMA通道转换完成标志
        /**对于DMA发送，DMA通道传输完成不代表数据全部发送完成，此时最后一字节数据还在UART的移位寄存器中还没发送完成，所以需要再等待最后一字节数据发送完成**/
        while(FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART0) == FL_RESET) {};
        FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);

        CHANNEL_2_TransferComplete = 1;
    }
}

void Uart0DMA_Config(uint8_t *buffer, uint32_t length)
{
    FL_DMA_ConfigTypeDef DMA_ConfigStruct = {0};

    DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;
    DMA_ConfigStruct.transmissionCount = length - 1;
    FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct, FL_DMA_CHANNEL_2);
}

void DMA_Uart0_TX(void)
{
    uint8_t TestTxData[11] = "TestUart-TX";

    FL_DMA_Enable(DMA);

    Uart0DMA_Config(TestTxData, 11);

    FL_UART_EnableTX(UART0);

}
