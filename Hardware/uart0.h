#ifndef __UART0_H
#define __UART0_H

#include "include.h" // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

// 串口0波特率
#ifndef UART0_BAUDRATE
#define UART0_BAUDRATE 115200
#endif // UART0_BAUDRATE

void uart0_config(void);
void uart0_sendbyte(u8 senddata);
void uart0_send_buff(u8* buf, u8 len); // 通过uart0发送若干数据

#endif
