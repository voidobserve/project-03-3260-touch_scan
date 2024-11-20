// 不能使用UART1+DMA来接收不定长的数据，这里的代码不能用
#include "uart1.h"

// 设置的波特率需要适配单片机的时钟，这里直接使用了官方的代码
#define USER_UART1_BAUD ((SYSCLK - UART1_BAUDRATE) / (UART1_BAUDRATE))
  
void uart1_config(void)
{
    // 电路板上，P11为发送引脚，P12为接收引脚
    P1_MD0 &= (~GPIO_P11_MODE_SEL(0x3) | ~GPIO_P12_MODE_SEL(0x3));
    P1_MD0 |= GPIO_P11_MODE_SEL(0x1); // 输出模式
    FOUT_S11 |= GPIO_FOUT_UART1_TX;   // 配置P11为UART1_TX
    FIN_S8 |= GPIO_FIN_SEL_P12;       // 配置P12为UART1_RX

    __EnableIRQ(UART1_IRQn); // 打开UART模块中断
    IE_EA = 1;               // 打开总中断

    UART1_BAUD1 = (USER_UART1_BAUD >> 8) & 0xFF; // 配置波特率高八位
    UART1_BAUD0 = USER_UART1_BAUD & 0xFF;        // 配置波特率低八位
    UART1_CON1 = UART_DMA_IRQ(0x1);              // DMA中断使能
    UART1_CON0 = UART_STOP_BIT(0x0) |            // 8bit数据，1bit停止位
                 UART_EN(0x1);
 

    UART1_DMAADRH = UART1_DMA_ADRH_VAL((((u16)uart1_rx_buf) >> 8) & 0xFF); // DMA地址高八位
    UART1_DMAADRL = UART1_DMA_ADRL_VAL((((u16)uart1_rx_buf) >> 0) & 0xFF); // DMA地址低八位
    UART1_DMALEN = UART1_DMA_LEN_VAL(RX_DMA_LEN);                          // DMA长度
    UART1_STA = UART_DMA_DONE(0x1);                                        // 清DMA状态标志
    UART1_DMACON = UART_RXDMA_KEY(0x1) | UART_RXDMA_EN(0x1);               // RXDMA使能
}

// UART1发送一个字节数据的函数
void uart1_sendbyte(u8 senddata)
{
    UART1_CON0 |= UART_EN(0x1);               // 使能串口进行发送
    while (!(UART1_STA & UART_TX_DONE(0x01))) // 等待前一次发送完成
        ;
    UART1_DATA = senddata;
    while (!(UART1_STA & UART_TX_DONE(0x01))) // 等待这次发送完成
        ;
    UART1_CON0 &= ~UART_EN(0x1); // 关闭串口停止发送
}

// UART1发送若干字节数据的函数
void uart1_sendbytes(u8 *buf, u32 buf_len)
{
    u32 i = 0;
    for (i = 0; i < buf_len; i++)
    {
        uart1_sendbyte(buf[i]);
    }
}

// UART1中断服务函数（DMA接收满才会触发该中断）
void UART1_IRQHandler(void) interrupt UART1_IRQn
{
    // 进入中断设置IP，不可删除
    __IRQnIPnPush(UART1_IRQn);

    // ---------------- 用户函数处理 -------------------

    // DMA完成中断,DMA处于空闲
    if (UART1_STA & UART_DMA_DONE(0x1))
    {
     
    }

    // 退出中断设置IP，不可删除
    __IRQnIPnPop(UART1_IRQn);
}
 
