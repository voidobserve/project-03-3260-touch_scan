/**
  ******************************************************************************
  * @file    uart_spi_i2c.h
  * @author  HUGE-IC Application Team
  * @version V1.0.0
  * @date    01-05-2021
  * @brief   This file contains all the UART SPI I2C LL firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 HUGE-IC</center></h2>
  *
  *
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_SPI_I2C_H__
#define __UART_SPI_I2C_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/***************************************************************************************************
|--------------------------------------------------------------------------------------------------|
|                                            UART                                                  |
|--------------------------------------------------------------------------------------------------|
***************************************************************************************************/

/***********************************************************************
|----------------------------------------------------------------------|
|             | Bit |                    Description                   |
|             |--------------------------------------------------------|
|             |  7  | 停止位控制位  0x0:1bit停止位  0x1:2bit停止位     |
|             |  6  | 将需要发送的第9bit数据写入该寄存器               |
|             |  5  | 1次发送9bit数据使能位  0x0:发送8bit  0x1:发送9bit|
|UART0/1_CON0 |  4  | UART使能位        0x0:不使能  0x1:使能           |
|             |  3  | TX电平取反控制位  0x0:不取反  0x1:取反           |
|             |  2  | RX电平取反控制位  0x0:不取反  0x1:取反           |
|             |  1  | TX中断使能位  0x0:不使能  0x1:使能               |
|             |  0  | RX中断使能位  0x0:不使能  0x1:使能               |
|------------------------------------------------------------------—---|
***********************************************************************/
// UART0/1_CON0
#define _UART0_CON0
#define _UART1_CON0
#define UART_STOP_BIT(n)             ((n) << 7)  // 停止位控制位  0x0:1bit停止位  0x1:2bit停止位
#define UART_NINTH_BIT(n)            ((n) << 6)  // 第9bit数据
#define UART_BIT9_EN(n)              ((n) << 5)  // 一次发送9bit数据使能位  0x0:发送8bit  0x1:发送9bit
#define UART_EN(n)                   ((n) << 4)  // UART使能位        0x0:不使能  0x1:使能
#define UART_TX_INV(n)               ((n) << 3)  // TX电平取反控制位  0x0:不取反  0x1:取反
#define UART_RX_INV(n)               ((n) << 2)  // RX电平取反控制位  0x0:不取反  0x1:取反
#define UART_TX_IRQ_EN(n)            ((n) << 1)  // TX中断使能位  0x0:不使能  0x1:使能
#define UART_RX_IRQ_EN(n)            ((n) << 0)  // RX中断使能位  0x0:不使能  0x1:使能

/**************************************************************************
|-------------------------------------------------------------------------|
|             | Bit |                    Description                      |
|             |-----------------------------------------------------------|
|             | 7:3 |                                                     |
| UART0/1_CON1|  2  | RX接收到地址标志位中断使能  0x0:不使能  0x1:使能    |
|             |  1  | 帧错误中断使能  0x0:不使能  0x1:使能                |
|             |  0  | DMA中断使能位  0x0:不使能  0x1:使能 (只有UART1支持) |
|------------------------------------------------------------------—------|
**************************************************************************/
// UART0/1_CON1
#define _UART0_CON1
#define _UART1_CON1
#define UART_RX_ADRR_IRQ(n)          ((n) << 2)  // RX接收到地址标志位中断使能  0x0:不使能  0x1:使能
#define UART_FERR_IRQ(n)             ((n) << 1)  // 帧错误中断使能  0x0:不使能  0x1:使能
#define UART_DMA_IRQ(n)              ((n) << 0)  // DMA中断使能位  0x0:不使能  0x1:使能 (只有UART1支持)

/********************************************************************************************************
|-------------------------------------------------------------------------------------------------------|
|             | Bit |                    Description                                                    |
|             |-----------------------------------------------------------------------------------------|
|             |  7  | 接收的第9bit,读该位读出第9bit数据                                                 |
|             |  6  | 接收到的奇偶校验位数据,奇偶校验由软件进行(接收8bit数据加奇                        |
| UART0/1_STA |     | 偶校验位时不使能BIT9_EN的情况下，在此位读出奇偶校验位)                            |
|             |  5  | RX状态标志位 该位为1表示buff接收满数据，写1清零或读取之后才会开始下一帧数据的接收 |
|             |  4  | TX状态标志位  0x0: 正在发送数据  0x1: 空闲                                        |
|             |  3  | 
|             |  2  | DMA状态标志位  0x0:正在忙  0x1:空闲
|             |  1  | TX状态标志位   0x0:数据    0x1:地址
|             |  0  | 
|-------------------------------------------------------------------------------------------------------|
********************************************************************************************************/
// UART0/1_STA
#define _UART0_STA
#define _UART1_STA
#define UART_RX_BIT9(n)              ((n) << 7)  // 接收的第9bit,读该位读出第9bit数据
#define UART_FERR_DATA(n)            ((n) << 6)  // 接收到的奇偶校验位数据,奇偶校验由软件进行(接收8bit数据加奇
                                                 // 偶校验位时不使能BIT9_EN的情况下，在此位读出奇偶校验位)
#define UART_RX_DONE(n)              ((n) << 5)  // RX状态标志位 该位为1表示buff接收满数据，
                                                 // 写1清零或读取之后才会开始下一帧数据的接收
#define UART_TX_DONE(n)              ((n) << 4)  // TX状态标志位  0x0: 正在发送数据  0x1: 空闲
#define UART_DMA_DONE(n)             ((n) << 2)  // DMA状态标志位  0x0:正在忙  0x1:空闲
#define UART_RX_ADDR_PND(n)          ((n) << 1)  // TX状态标志位   0x0:数据    0x1:地址

/************************************************************************************
|-----------------------------------------------------------------------------------|
|             | Bit |                    Description                                |
|             |---------------------------------------------------------------------|
|UART0/1_BAUD0| 7:0 | 波特率寄存器低八位,UART波特率寄存器,计算公式:sysclk/(baud+1)  |
|-----------------------------------------------------------------------------------|
************************************************************************************/
// UART0/1_BAUD0
#define _UART0_BAUD0
#define _UART1_BAUD0
#define UART_BAUD_L(n)               ((n) << 0)  // 波特率寄存器低八位,UART波特率寄存器,计算公式:sysclk/(baud+1)

/************************************************************************************
|-----------------------------------------------------------------------------------|
|             | Bit |                    Description                                |
|             |---------------------------------------------------------------------|
|UART0/1_BAUD1| 7:0 | 波特率寄存器高八位,UART波特率寄存器,计算公式:sysclk/(baud+1)  |
|-----------------------------------------------------------------------------------|
************************************************************************************/
// UART0/1_BAUD1
#define _UART0_BAUD1
#define _UART1_BAUD1
#define UART_BAUD_L(n)               ((n) << 0)  // 波特率寄存器高八位,UART波特率寄存器,计算公式:sysclk/(baud+1)

/*********************************************************************************************
|--------------------------------------------------------------------------------------------|
|             | Bit |                    Description                                         |
|             |------------------------------------------------------------------------------|
|UART0/1_DATA | 7:0 | 使能之后向该寄存器写入数据则触发该数据的发送,读该寄存器取得接收的数据  |
|--------------------------------------------------------------------------------------------|
*********************************************************************************************/
// UART0/1_DATA
#define _UART0_DATA
#define _UART1_DATA
#define UART_DATA(n)                 ((n) << 0)  // 使能之后向该寄存器写入数据则触发该数据的发送,读该寄存器取得接收的数据

/*******************************************************************************
|------------------------------------------------------------------------------|
|             | Bit |                    Description                           |
|             |----------------------------------------------------------------|
|             | 7:4 |                                                          |
|             |  3  | TXDMA的使能KEY,使能TXDMA时这一位需要同时置1,否则使能无效 |
| UART1_DMACON|  2  | RXDMA的使能KEY,使能RXDMA时这一位需要同时置1,否则使能无效 |
|             |  1  | TXDMA使能信号,DMA完成后硬件自动清零                      |
|             |  0  | RXDMA使能信号,DMA完成后硬件自动清零                      |
|------------------------------------------------------------------------------|
*******************************************************************************/
// UART1_DMACON
#define _UART1_DMACON
#define UART_TXDMA_KEY(n)            ((n) << 3)  // TXDMA的使能KEY,使能TXDMA时这一位需要同时置1,否则使能无效
#define UART_RXDMA_KEY(n)            ((n) << 2)  // RXDMA的使能KEY,使能RXDMA时这一位需要同时置1,否则使能无效
#define UART_TXDMA_EN(n)             ((n) << 1)  // TXDMA使能信号,DMA完成后硬件自动清零
#define UART_RXDMA_EN(n)             ((n) << 0)  // RXDMA使能信号,DMA完成后硬件自动清零

/*******************************************************************************
|------------------------------------------------------------------------------|
|              | Bit |                    Description                          |
|              |---------------------------------------------------------------|
| UART1_DMAADRH| 7:0 | DMA地址高八位                                           |
|------------------------------------------------------------------------------|
*******************************************************************************/
// UART1_DMAADRH
#define _UART1_DMAADRH
#define UART1_DMA_ADRH_VAL(n)        ((n) << 0)  // DMA地址高八位

/*******************************************************************************
|------------------------------------------------------------------------------|
|              | Bit |                    Description                          |
|              |---------------------------------------------------------------|
| UART1_DMAADRL| 7:0 | DMA地址低八位                                           |
|------------------------------------------------------------------------------|
*******************************************************************************/
// UART1_DMAADRL
#define _UART1_DMAADRL
#define UART1_DMA_ADRL_VAL(n)        ((n) << 0)  // DMA地址低八位

/*******************************************************************************
|------------------------------------------------------------------------------|
|              | Bit |                    Description                          |
|              |---------------------------------------------------------------|
| UART1_DMALEN | 7:5 |                                                         |
|              | 4:0 | DMA长度寄存器                                           |
|------------------------------------------------------------------------------|
*******************************************************************************/
// UART1_DMALEN
#define _UART1_DMALEN
#define UART1_DMA_LEN_VAL(n)         ((n) << 0)  // DMA长度寄存器



/***************************************************************************************************
|--------------------------------------------------------------------------------------------------|
|                                            SPI                                                   |
|--------------------------------------------------------------------------------------------------|
***************************************************************************************************/

/****************************************************************************************************
|---------------------------------------------------------------------------------------------------|
|          | Bit |                    Description                                                   |
|          |----------------------------------------------------------------------------------------|
|          |  7  |                                                                                  |
|          |  6  | 主从机控制位  0x0:主机  0x1:从机                                                 |
|          |  5  | 发送接收控制位  0x0:发送数据  0x1:接收数据                                       |
| SPI_CON  |  4  | 2线或3线选择位  0x0:2线模式  0x1:3线模式                                         |
|          |  3  | SPI中断使能位  0x0:不使能  0x1:使能                                              |
|          |  2  | 采样模式选择位  0x0:上升沿发送数据,下降沿采样  0x1:下降沿发送数据,上升沿发送数据 |
|          |  1  | 时钟线空闲状态选择位  0x0:CLK空闲为低电平  0x1:CLK空闲为高电平                   |
|          |  0  | SPI使能位  0x0:不使能  0x1:使能                                                  |
|---------------------------------------------------------------------------------------------------|
****************************************************************************************************/
// SPI_CON
#define _SPI_CON
#define SPI_MASTER_SLAVE_SEL(n)      ((n) << 6)  // 主从机控制位  0x0:主机  0x1:从机
#define SPI_RX_TX_SEL(n)             ((n) << 5)  // 发送接收控制位  0x0:发送数据  0x1:接收数据
#define SPI_2W_3W_SEL(n)             ((n) << 4)  // 2线或3线选择位  0x0:3线模式  0x1:2线模式
#define SPI_IRQ_EN(n)                ((n) << 3)  // SPI中断使能位  0x0:不使能  0x1:使能
#define SPI_SMP_SEL(n)               ((n) << 2)  // 采样模式选择位  0x0:上升沿发送数据,下降沿采样  0x1:下降沿发送数据,上升沿发送数据
#define SPI_CLK_IDLE_STA(n)          ((n) << 1)  // 时钟线空闲状态选择位   0x0:CLK空闲为低电平  0x1:CLK空闲为高电平
#define SPI_EN(n)                    ((n) << 0)  // SPI使能位  0x0:不使能  0x1:使能

/**********************************************************************************
|---------------------------------------------------------------------------------|
|           | Bit |                    Description                                |
|           |---------------------------------------------------------------------|
| SPI_BAUD  | 7:0 | 波特率控制寄存器  计算公式: 波特率 = clk/(2*(SPI_BAUD+1))    |
|---------------------------------------------------------------------------------|
**********************************************************************************/
// SPI_BAUD
#define _SPI_BAUD
#define SPI_BAUD(n)                  ((n) << 0)  // 波特率控制寄存器  计算公式: 波特率 = clk/(2*(SPI_BAUD+1))

/**********************************************************************************
|---------------------------------------------------------------------------------|
|           | Bit |                    Description                                |
|           |---------------------------------------------------------------------|
| SPI_DATA  | 7:0 | 使能后将数据写入DATA触发发送,读DATA则读出接收到的数据         |
|---------------------------------------------------------------------------------|
**********************************************************************************/
// SPI_DATA
#define _SPI_DATA
#define SPI_DATA(n)                  ((n) << 0)  // 使能后将数据写入DATA触发发送,读DATA则读出接收到的数据

/**********************************************************************************
|---------------------------------------------------------------------------------|
|           | Bit |                    Description                                |
|           |---------------------------------------------------------------------|
| SPI_STA   | 7:2 |                                                               |
|           |  1  | SPI中断标志  写1清零                                          |
|           |  0  | SPI状态标志位  0x0:正在发送或正在接收  0x1:空闲               |
|---------------------------------------------------------------------------------|
**********************************************************************************/
// SPI_STA
#define _SPI_STA
#define SPI_IRQ_FLAG(n)              ((n) << 1)  // SPI中断标志  写1清零
#define SPI_STA_FLAG(n)              ((n) << 0)  // SPI状态标志位  0x0:正在发送或正在接收  0x1:空闲



/***************************************************************************************************
|--------------------------------------------------------------------------------------------------|
|                                            I2C                                                   |
|--------------------------------------------------------------------------------------------------|
***************************************************************************************************/

/***************************************************************************************************
|--------------------------------------------------------------------------------------------------|
|          | Bit |                    Description                                                  |
|          |---------------------------------------------------------------------------------------|
|          |  7  | I2C使能位  0x0:"sdao"和"sclo"输出1，并忽略"sdai"和"scli"输入  0x1:使能I2C模块   |
|          |  6  | 起始位  0x0:无操作  0x1:检查I2C总线,如果总线处于空闲状态,                       |
|          |     |         并且模块处于主机模式,则发送一个起始位                                   |
|          |  5  | 停止位  0x0:无操作  0x1:当模块处于主机模式，则发送一个停止位                    |
| I2C_CON  |  4  | SI清除位  写1清除SI，读恒为0                                                    |
|          |  3  | 应答控制位  0x0:当出现以下情况时发送NACK:                                       |
|          |     |                  * 在主机接收模式下接收完1byte;                                 |
|          |     |                  * 在从机接收模式下接收完1byte                                  |
|          |     |             0x1:当出现以下情况时发送ACK:                                        |
|          |     |                  * 接收到本机从机地址;                                          |
|          |     |                  * 在广播地址位使能的情况下接收到广播地址;                      |
|          |     |                  * 主机接收情况下接收到1byte                                    |
|          |     |             从机接收情况下接收到1byte                                           |
|          | 2:0 | 波特率控制位(CR)                                                                |
|          |     | I2C波特率由以下公式计算得出:baud(kHz)=sysclk/x,其中x的值由CR寄存器决定,分别是:  |
|          |     | 0x00:256  0x01:224  0x02:160  0x03:80  0x04:1024  0x05:120  0x06:60             |
|          |     | 0x07:当CR设置为0x07时,波特率由Timer0的pwm频率决定,计算方法为Timer0的pwm频率除以8|
|--------------------------------------------------------------------------------------------------|
***************************************************************************************************/
// I2C_CON
#define _I2C_CON
#define I2C_EN(n)                    ((n) << 7)  // I2C使能位  0x0:"sdao"和"sclo"输出1，并忽略"sdai"和"scli"输入  0x1:使能I2C模块
#define I2C_START_BIT(n)             ((n) << 6)  // 0x0:无操作  0x1:检查I2C总线，如果总线处于空闲状态，并且模块处于主机模式，则发送一个起始位
#define I2C_STOP_BIT(n)              ((n) << 5)  // 0x0:无操作  0x1:当模块处于主机模式，则发送一个停止位
#define I2C_SI_CLEAR(n)              ((n) << 4)  // SI清除位  写1清除SI，读恒为0
#define I2C_ACK_NACK_BIT(n)          ((n) << 3)  // 应答控制位  0x0:当出现以下情况时发送NACK:
                                                  //                  * 在主机接收模式下接收完1byte;
                                                  //                  * 在从机接收模式下接收完1byte
                                                  //             0x1:当出现以下情况时发送ACK:
                                                  //                  * 接收到本机从机地址;
                                                  //                  * 在广播地址位使能的情况下接收到广播地址;
                                                  //              ?  * 主机接收情况下接收到1byte
                                                  //             从机接收情况下接收到1byte
#define I2C_CR_SEL(n)                ((n) << 0)  // 波特率控制位(CR):
                                                  // I2C波特率由以下公式计算得出:baud(kHz)=sysclk/x,其中x的值由CR寄存器决定,分别是:  
                                                  // 0x00:256  0x01:224  0x02:160  0x03:80  0x04:1024  0x05:120  0x06:60             
                                                  // 0x07:当CR设置为0x07时,波特率由Timer0的pwm频率决定,计算方法为Timer0的pwm频率除以8

/***************************************************************************************
|--------------------------------------------------------------------------------------|
|           | Bit |                    Description                                     |
|           |--------------------------------------------------------------------------|
| I2C_STA   | 7:3 | 模块状态标志位                                                     |
|           |  2  | 除了0xF8状态之外的所有状态都会将SI置位,SI_CLR写1和读DATA都会清除SI |
|           |  1  | 中断标志位,当使能了中断后,随SI置位                                 |
|           |  0  | 中断使能位                                                         |
|--------------------------------------------------------------------------------------|
***************************************************************************************/
// I2C_STA
#define _I2C_STA
#define I2C_STA_FLAG(n)              ((n) << 3)  // 模块状态标志位
#define I2C_SI_STA(n)                ((n) << 2)  // 除了0xF8状态之外的所有状态都会将SI置位,SI_CLR写1和读DATA都会清除SI
#define I2C_IRQ_FLAG(n)              ((n) << 1)  // 中断标志位,当使能了中断后,随SI置位
#define I2C_IRQ_EN(n)                ((n) << 0)  // 中断使能位

/**********************************************************************************
|---------------------------------------------------------------------------------|
|           | Bit |                    Description                                |
|           |---------------------------------------------------------------------|
|  I2C_ADR  | 7:1 | 本模块从机地址                                                |
|           |  0  | 广播地址控制位  0x0:忽略广播地址  0x1:响应广播地址            |
|---------------------------------------------------------------------------------|
**********************************************************************************/
// I2C_ADR
#define _I2C_ADR
#define I2C_ADDR(n)                  ((n) << 1)  // 本模块从机地址
#define I2C_GC_CTRL(n)               ((n) << 0)  // 广播地址控制位  0x0:忽略广播地址  0x1:响应广播地址

/**********************************************************************************
|---------------------------------------------------------------------------------|
|           | Bit |                    Description                                |
|           |---------------------------------------------------------------------|
|  I2C_DATA | 7:0 | 数据寄存器                                                    |
|---------------------------------------------------------------------------------|
**********************************************************************************/
// I2C_DATA
#define _I2C_DATA
#define I2C_DATA(n)                  ((n) << 0)  // 数据寄存器

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif // __UART_SPI_I2C_H__

/**
  * @}
  */

/**
  * @}
  */

/*************************** (C) COPYRIGHT 2021 HUGE-IC ***** END OF FILE *****/
