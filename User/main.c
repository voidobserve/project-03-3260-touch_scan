/**
 ******************************************************************************
 * @file    main.c
 * @author  HUGE-IC Application Team
 * @version V1.0.0
 * @date    05-11-2022
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2021 HUGE-IC</center></h2>
 *
 * 版权说明后续补上
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "include.h"

/** @addtogroup Template_Project
 * @{
 */



void main(void)
{
    // 看门狗默认打开, 复位时间2s
    system_init();

    WDT_KEY = WDT_KEY_VAL(0xDD); //  关闭看门狗

    // 关闭HCK和HDA的调试功能
    WDT_KEY = 0x55;  // 解除写保护
    IO_MAP &= ~0x01; // 清除这个寄存器的值，实现关闭HCK和HDA引脚的调试功能（解除映射）
    WDT_KEY = 0xBB;

    /* 用户代码初始化接口 */
    // user_init();
    {                    // user_init();
       
        uart0_config();          // 发送和接收指令使用到的串口
      
    } // user_init();




    /* 按键初始化 */
    tk_param_init();

    // P1_MD0 &= (~GPIO_P11_MODE_SEL(0x3));
    // P1_MD0 |= GPIO_P11_MODE_SEL(0x1); // 输出模式
    // FOUT_S11 |= GPIO_FOUT_AF_FUNC;

    /* 系统主循环 */
    while (1)
    {
        /* 按键扫描函数 */
        __tk_scan(); // 使用了库里面的接口（闭源库）

        /* 用户循环扫描函数接口 */
        touch_key_scan();
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
