// my_config.h -- 自定义的配置文件
#ifndef __MY_CONFIG_H
#define __MY_CONFIG_H

#include "include.h" // 使用芯片官方提供的头文件

#define ARRAY_SIZE(arry) (sizeof(arry) / sizeof(arry[0]))

#define USE_MY_DEBUG 1

// 串口0波特率
#define UART0_BAUDRATE (115200)
// 串口1波特率
// #define UART1_BAUDRATE 115200 // 这款芯片（TX3260）不能使用UART1的DMA来接收不定长的数据

// 串口0接收缓冲区的大小（单位：字节）
#define UART0_RXBUF_LEN (30) // 最大不能超过255，超过之后，串口接收会出错

// 扫描时间配置：

// ======================================================
// 触摸按键配置
#define TOUCH_KEY_ONE_LEFT TK_CH14_VALIB   // 左侧数下来，第一个触摸按键
#define TOUCH_KEY_TWO_LEFT TK_CH13_VALIB   // 左侧数下来，第二个触摸按键
#define TOUCH_KEY_THREE_LEFT TK_CH12_VALIB // 左侧数下来，第三个触摸按键

#define TOUCH_KEY_ONE_RIGHT TK_CH9_VALIB    // 右侧数下来，第一个触摸按键
#define TOUCH_KEY_TWO_RIGHT TK_CH10_VALIB   // 右侧数下来，第二个触摸按键
#define TOUCH_KEY_THREE_RIGHT TK_CH11_VALIB // 右侧数下来，第三个触摸按键

// 触摸按键键值定义：
#define TOUCH_KEY_VAL_MUTE (0x0040)    // 左2
#define TOUCH_KEY_VAL_VOL_INC (0x0041) // 左1
#define TOUCH_KEY_VAL_VOL_DEC (0x0042) // 左3
#define TOUCH_KEY_VAL_MODE (0x0065)    // 右2
#define TOUCH_KEY_VAL_PRE (0x00E3)     // 右3
#define TOUCH_KEY_VAL_NEXT (0x00E4)    // 右1

// 检测到长按时要发送的键值：
#define TOUCH_KEY_VAL_POWER (0x0046) // 左2
#define TOUCH_KEY_VAL_MAIN (0x0011)  // 右2

// 注意：只有 TOUCH_KEY_VAL_VOL_INC 和 TOUCH_KEY_VAL_VOL_DEC 需要检测持续按下

// #define DETECT_DOUBLE_CLICK_INTERVAL (100) // 检测双击的时间间隔(单位：ms)
#define LONG_PRESS_TIME_THRESHOLD_MS (750) // 长按时间阈值（单位：ms）
#define HOLD_PRESS_TIME_THRESHOLD_MS (150) // 长按持续(不松手)的时间阈值(单位：ms)，每隔 xx 时间认为有一次长按持续事件
#define LOOSE_PRESS_CNT_MS (50)            // 松手计时，松开手多久，才认为是真的松手了
#define ONE_CYCLE_TIME_MS (0)              // 主函数完成一次循环所需的时间，单位：ms (0--说明每次调用该函数的时间很短，可以忽略不计)
// 触摸按键配置
// ======================================================

// #define USE_MY_DEBUG 1

#include <stdio.h> // printf()

#include "uart0.h" // 接收 / 发送 指令 使用的串口

#include "instruction.h" // 扫描接收到的数据（必须要在串口0的头文件后面，串口要先接收并验证，才轮到它扫描指令）
#include "send_data.h"   // 发送带有数据的指令

#endif // end file
