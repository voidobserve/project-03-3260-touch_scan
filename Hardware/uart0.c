#include "uart0.h"

#include <string.h> // memset()

// 设置的波特率需要适配单片机的时钟，这里直接使用了官方的代码
#define USER_UART0_BAUD ((SYSCLK - UART0_BAUDRATE) / (UART0_BAUDRATE))

// 重写putchar()函数
char putchar(char c)
{
    uart0_sendbyte(c);
    return c;
}

// uart0初始化
// 波特率由宏 UART0_BAUDRATE 来决定
// P00 作为打印调试脚
void uart0_config(void)
{

    P0_MD0 &= (~GPIO_P00_MODE_SEL(0x3));
    P0_MD0 |= GPIO_P00_MODE_SEL(0x1); // 输出模式
    FOUT_S00 |= GPIO_FOUT_UART0_TX;   // 配置P00为UART0_TX

    // __EnableIRQ(UART0_IRQn); // 打开UART模块中断
    // IE_EA = 1;               // 打开总中断

    UART0_BAUD1 = (USER_UART0_BAUD >> 8) & 0xFF; // 配置波特率高八位
    UART0_BAUD0 = USER_UART0_BAUD & 0xFF;        // 配置波特率低八位
    UART0_CON0 = UART_STOP_BIT(0x0) |
                 UART_RX_IRQ_EN(0x1) |
                 UART_EN(0x1); // 8bit数据，1bit停止位，使能RX中断
}

// UART0中断服务函数（接收中断）
void UART0_IRQHandler(void) interrupt UART0_IRQn
{
    // 进入中断设置IP，不可删除
    __IRQnIPnPush(UART0_IRQn);
    // ---------------- 用户函数处理 -------------------
    // RX接收完成中断
    if (UART0_STA & UART_RX_DONE(0x1))
    {

    } // if (UART0_STA & UART_RX_DONE(0x1))

    // 退出中断设置IP，不可删除
    __IRQnIPnPop(UART0_IRQn);
}

// UART0发送一个字节数据的函数
void uart0_sendbyte(u8 senddata)
{
    while (!(UART0_STA & UART_TX_DONE(0x01)))
        ;
    UART0_DATA = senddata;
    while (!(UART0_STA & UART_TX_DONE(0x01))) // 等待这次发送完成
        ;
}

// 通过uart0发送若干数据
void uart0_send_buff(u8 *buf, u8 len)
{
    u8 i = 0;
    for (; i < len; i++)
    {
        uart0_sendbyte(buf[i]);
    }
}
