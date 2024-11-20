#include "instruction.h"

#include <string.h>

// 用bit定义，来节省空间
volatile bit flag_get_all_status = 0;    // 获取所有功能的状态
volatile bit flag_get_gear = 0;          // 获取挡位状态 / 得到了挡位的状态
volatile bit flag_get_battery = 0;       // 获取电池状态 / 得到了电池的状态（电池电量，单位：百分比）
volatile bit flag_get_brake = 0;         // 获取刹车状态 / 得到了刹车的状态
volatile bit flag_get_left_turn = 0;     // 获取左转向灯的状态 / 得到了左转向灯的状态
volatile bit flag_get_right_turn = 0;    // 获取右转向灯的状态 / 得到了右转向灯的状态
volatile bit flag_get_high_beam = 0;     // 获取远光灯的状态 / 得到了远光灯的状态
volatile bit flag_get_engine_speed = 0;  // 获取发动机的转速 / 得到了发动机的转速
volatile bit flag_get_speed = 0;         // 获取时速 / 得到了时速
volatile bit flag_get_fuel = 0;          // 获取油量 / 得到了油量（单位：百分比）
// volatile bit flag_get_temp_of_water = 0; // 获取水温 / 得到了水温 

volatile bit flag_get_total_mileage = 0;     // 获取大计里程 / 得到了大计里程
volatile bit flag_get_sub_total_mileage = 0; // 获取小计里程 / 得到了小计里程

// volatile bit flag_get_touch_key_status = 0; // 获取触摸按键的状态
volatile bit flag_alter_date = 0;           // 修改日期
volatile bit flag_alter_time = 0;           // 修改时间

volatile bit flag_get_voltage_of_battery = 0;    // 获取电池电压
volatile bit flag_set_temp_of_water_warning = 0; // 设置水温报警

volatile bit flag_clear_total_mileage = 0;     // 清除大计里程
volatile bit flag_clear_sub_total_mileage = 0; // 清除小计里程

// // 存放接收到的设置水温报警的指令中，对应的操作，默认为无操作
// volatile u8 operation_set_temp_of_water_warning = OPERATION_SET_TEMP_OF_WATER_WARNING_NONE;

// 检查接收是否正确的函数，如果接收正确，
// 根据接收到的数据中的指令，给对应的指令的标志位置一
void instruction_scan(void)
{
    u8 i = 0; // 注意要大于等于缓冲区能存放的指令数目

    for (i = 0; i < (UART0_RXBUF_LEN) / (FRAME_MAX_LEN); i++)
    {
        if (flagbuf_valid_instruction[i]) // 如果对应的位置有合法的数据帧
        {
            // 根据接收到数据中的指令，给对应的指令的标志位置一
            // if (4 == uart0_recv_buf[i][1]) // 如果是四位长度的指令
            {
                switch (uart0_recv_buf[i][2]) // 根据不同的指令来给对应的标志位置一
                {
                case INSTRUCTION_GET_ALL_STATUS: // 获取所有功能的状态
                    flag_get_all_status = 1;
                    break;


                case INSTRUCTION_ALTER_DATE: // 修改日期
                    flag_alter_date = 1;
                    // fun_info.date = ((u32)uart0_recv_buf[i][3] << 24) + /* 年 */
                    //                 ((u32)uart0_recv_buf[i][4] << 16) +
                    //                 ((u32)uart0_recv_buf[i][5] << 8) + /* 月 */
                    //                 ((u32)uart0_recv_buf[i][6] << 0);  /* 日 */
                    fun_info.save_info.year = ((u16)uart0_recv_buf[i][3] << 8) +
                                              (u16)uart0_recv_buf[i][4];
                    fun_info.save_info.month = uart0_recv_buf[i][5];
                    fun_info.save_info.day = uart0_recv_buf[i][6];

                    break;

                case INSTRUCTION_ALTER_TIME: // 修改时间
                    flag_alter_time = 1;
                    // 例：A5 07 2F 0D 37 18 07
                    fun_info.save_info.time_hour = uart0_recv_buf[i][3];
                    fun_info.save_info.time_min = uart0_recv_buf[i][4];
                    fun_info.save_info.time_sec = uart0_recv_buf[i][5];
                    break;

                case INSTRUCTION_CLEAR_TOTAL_MILEAGE: // 清除大计里程
                    flag_clear_total_mileage = 1;
                    break;

                case INSTRUCTION_CLEAR_SUBTOTAL_MILEAGE: // 清除小计里程
                    flag_clear_sub_total_mileage = 1;
                    break;
                }

                if (recv_frame_cnt > 0) //
                {
                    recv_frame_cnt--; // 从串口接收的数据帧数目减一，表示指令已经从缓冲区取出
                }

                flagbuf_valid_instruction[i] = 0; // 清空缓冲区对应的元素，表示该下标的指令已经处理
                uart0_recv_len[i] = 0;
                recved_flagbuf[i] = 0;
                memset(uart0_recv_buf[i], 0, FRAME_MAX_LEN); // 清空缓冲区对应的元素
            } // if (4 == uart0_recv_buf[i][1])
        }
    }
}

void instruction_handle(void)
{
    if (flag_get_all_status)
    {
        // 如果要获取所有功能的状态
        u32 temp_val = 0;        // 临时变量(在发送日期和时间使用到)
        flag_get_all_status = 0; // 清除标志位

#if USE_MY_DEBUG
        printf(" flag_get_all_status\n");
#endif

        // 获取所有功能的状态，需要把这些功能对应的状态都发送出去
        send_data(SEND_GEAR, fun_info.gear);                                         // 1. 发送当前挡位的状态
        send_data(SEND_BATTERY, fun_info.battery);                                   // 2. 发送电池电量
        send_data(SEND_BARKE, fun_info.brake);                                       // 3. 发送当前刹车的状态
        send_data(SEND_LEFT_TURN, fun_info.left_turn);                               // 4. 发送当前左转向灯的状态
        send_data(SEND_RIGHT_TURN, fun_info.right_turn);                             // 5. 发送当前右转向灯的状态
        send_data(SEND_HIGH_BEAM, fun_info.high_beam);                               // 6. 发送当前远光灯的状态
        send_data(SEND_ENGINE_SPEED, fun_info.engine_speeed);                        // 7. 发送发动机转速
        send_data(SEND_SPEED, fun_info.speed);                                       // 8. 发送当前采集到的车速（时速）
        send_data(SEND_FUEL, fun_info.fuel);                                         // 9. 发送当前油量(单位：百分比)
        send_data(SEND_WATER_TEMP, fun_info.temp_of_water);                          // 10. 发送当前采集的水温
#ifdef USE_INTERNATIONAL                                                             // 公制单位
        send_data(SEND_TOTAL_MILEAGE, fun_info.save_info.total_mileage / 100);       // 11. 发送大计里程（只发送百米及以上的数据）
        send_data(SEND_SUBTOTAL_MILEAGE, fun_info.save_info.subtotal_mileage / 100); // 12. 发送小计里程(只发送百米及以上的数据)
#endif                                                                               // USE_INTERNATIONAL 公制单位

#ifdef USE_IMPERIAL // 英制单位

        send_data(SEND_TOTAL_MILEAGE, fun_info.save_info.total_mileage / 161);       // 11. 发送大计里程（只发送0.1英里及以上的数据）
        send_data(SEND_SUBTOTAL_MILEAGE, fun_info.save_info.subtotal_mileage / 161); // 12. 发送小计里程(只发送0.1英里及以上的数据)

#endif // USE_IMPERIAL 英制单位

        // 13. 发送触摸按键的状态
        // send_data(SEND_TOUCH_KEY_STATUS, fun_info.touch_key_val);
        // 14. 发送当前日期
        temp_val = ((u32)fun_info.save_info.year << 16) |
                   ((u32)fun_info.save_info.month << 8) |
                   fun_info.save_info.day;
        send_data(SEND_DATE, temp_val);
        // 15. 发送当前时间
        temp_val = ((u32)fun_info.save_info.time_hour << 16) |
                   ((u32)fun_info.save_info.time_min << 8) |
                   fun_info.save_info.time_sec;
        send_data(SEND_TIME, temp_val);
        // 16. 发送当前的电池电压
        send_data(SEND_VOLTAGE_OF_BATTERY, fun_info.voltage_of_battery);
        // 17. 发送当前的水温报警状态
        send_data(SEND_TEMP_OF_WATER_ALERT, fun_info.flag_is_in_water_temp_warning);
    }

    if (flag_get_gear)
    {
        // 如果要获取挡位的状态
        flag_get_gear = 0; //

#if USE_MY_DEBUG
        printf(" flag_get_gear\n");
#endif

        send_data(SEND_GEAR, fun_info.gear); // 发送当前挡位的状态
    }

    if (flag_get_battery)
    {
        // 如果要获取电池电量的状态
        flag_get_battery = 0;
#if USE_MY_DEBUG
        printf(" flag_get_battery\n");
#endif

        send_data(SEND_BATTERY, fun_info.battery); // 发送电池电量
    }

    if (flag_get_brake)
    {
        // 如果要获取获取刹车的状态
        flag_get_brake = 0;

#if USE_MY_DEBUG
        printf(" flag_get_brake\n");
#endif

        send_data(SEND_BARKE, fun_info.brake); // 发送当前刹车的状态
    }

    if (flag_get_left_turn)
    {
        // 如果要获取左转向灯的状态
        flag_get_left_turn = 0;

#if USE_MY_DEBUG
        printf(" flag_get_left_turn\n");
#endif

        send_data(SEND_LEFT_TURN, fun_info.left_turn); // 发送当前左转向灯的状态
    }

    if (flag_get_right_turn)
    {
        // 如果要获取右转向灯的状态
        flag_get_right_turn = 0;
#if USE_MY_DEBUG
        printf(" flag_get_right_turn\n");
#endif
        send_data(SEND_RIGHT_TURN, fun_info.right_turn); // 发送当前右转向灯的状态
    }

    if (flag_get_high_beam)
    {
        // 如果要获取远光灯的状态
        flag_get_high_beam = 0;
#if USE_MY_DEBUG
        printf(" flag_get_high_beam\n");
#endif
        send_data(SEND_HIGH_BEAM, fun_info.high_beam); // 发送当前远光灯的状态
    }

    if (flag_get_engine_speed)
    {
        // 如果要获取发动机的转速
        flag_get_engine_speed = 0;
#if USE_MY_DEBUG
        printf(" flag_get_engine_speed \n");
        printf(" cur engine speed %u rpm ", (u16)fun_info.engine_speeed);
#endif
        send_data(SEND_ENGINE_SPEED, fun_info.engine_speeed);
    }

    if (flag_get_speed)
    {
        // 如果要获取时速
        flag_get_speed = 0;
#if USE_MY_DEBUG
        printf(" flag_get_speed \n");
#endif

#ifdef USE_INTERNATIONAL // 使用公制单位

        send_data(SEND_SPEED, fun_info.speed); // 发送当前采集到的车速（时速）

#endif // USE_INTERNATIONAL 使用公制单位

#ifdef USE_IMPERIAL // 使用英制单位

        send_data(SEND_SPEED, fun_info.speed * 621 / 1000);

#endif
    }

    if (flag_get_fuel)
    {
        // 如果要获取油量
        flag_get_fuel = 0;

#if USE_MY_DEBUG
        printf(" flag_get_fuel \n");
#endif

        send_data(SEND_FUEL, fun_info.fuel);
    }

// 不用发送水温，改为发送水温报警
//     if (flag_get_temp_of_water)
//     {
//         // 如果要获取水温
//         flag_get_temp_of_water = 0;
// #if USE_MY_DEBUG
//         printf(" flag_get_temp_of_water \n");
// #endif
//         send_data(SEND_WATER_TEMP, fun_info.temp_of_water);
//     }

    if (flag_get_total_mileage)
    {
        // 如果要获取大计里程 / 得到了大计里程新的数据
        flag_get_total_mileage = 0;
#if USE_MY_DEBUG
        printf(" flag_get_total_mileage \n");
        printf(" cur total mileage %lu /0.1km \n", (u32)fun_info.save_info.total_mileage);
#endif

#ifdef USE_INTERNATIONAL // 公制单位

        // 只发送百米及以上的数据
        send_data(SEND_TOTAL_MILEAGE, fun_info.save_info.total_mileage / 100);

#endif // USE_INTERNATIONAL 公制单位

#ifdef USE_IMPERIAL // 英制单位

#if USE_MY_DEBUG
        printf("total mileage: %lu * 0.1 mile", fun_info.save_info.total_mileage / 161);
#endif // USE_MY_DEBUG

        // 只发送0.1英里及以上的数据
        send_data(SEND_TOTAL_MILEAGE, fun_info.save_info.total_mileage / 161);

#endif // USE_IMPERIAL 英制单位
    }

    if (flag_get_sub_total_mileage)
    {
        // 如果要获取小计里程 / 得到了小计里程新的数据
        flag_get_sub_total_mileage = 0;
#if USE_MY_DEBUG
        printf(" flag_get_sub_total_mileage \n");
        printf(" cur subtotal mileage %lu /0.1km \n", (u32)fun_info.save_info.subtotal_mileage);
#endif // USE_MY_DEBUG

#ifdef USE_INTERNATIONAL // 公制单位

        // 只发送百米及以上的数据
        send_data(SEND_SUBTOTAL_MILEAGE, fun_info.save_info.subtotal_mileage / 100);
#endif // USE_INTERNATIONAL 公制单位

#ifdef USE_IMPERIAL // 英制单位

#if USE_MY_DEBUG
        printf("sub total mileage: %lu mile", fun_info.save_info.subtotal_mileage / 161);
#endif // USE_MY_DEBUG
       // 只发送0.1英里及以上的数据
       // 变量中存放的是以m为单位的数据，需要做转换再发送
        send_data(SEND_SUBTOTAL_MILEAGE, fun_info.save_info.subtotal_mileage / 161);

#endif // USE_IMPERIAL 英制单位
    }

//     if (flag_get_touch_key_status)
//     {
//         // 如果要获取触摸按键的状态 / 得到了触摸按键的状态
//         flag_get_touch_key_status = 0;
// #if USE_MY_DEBUG
//         printf(" flag_get_touch_key_status \n");
// #endif
//         send_data(SEND_TOUCH_KEY_STATUS, fun_info.touch_key_val);
//     }

    if (flag_alter_date)
    {
        // 如果要修改日期
        flag_alter_date = 0;
#if USE_MY_DEBUG
        printf(" flag_alter_date \n");
        printf("year %d month %d day %d \n", (u16)fun_info.save_info.year, (u16)fun_info.save_info.month, (u16)fun_info.save_info.day);
#endif

        fun_info_save(); // 将日期信息写回flash
    }

    if (flag_alter_time)
    {
        // 如果要修改时间
        flag_alter_time = 0;

#if USE_MY_DEBUG
        printf(" flag_alter_time \n");
        printf("hour %d min %d sec %d \n", (u16)fun_info.save_info.time_hour, (u16)fun_info.save_info.time_min, (u16)fun_info.save_info.time_sec);
#endif

        fun_info_save(); // 将时间信息写回flash
    }

    if (flag_get_voltage_of_battery)
    {
        // 如果要获取电池电压
        flag_get_voltage_of_battery = 0;
#if USE_MY_DEBUG
        printf(" flag_get_voltage_of_battery \n");
        printf(" cur voltage of battery %u \n", (u16)fun_info.voltage_of_battery);
#endif
        send_data(SEND_VOLTAGE_OF_BATTERY, fun_info.voltage_of_battery);
    }

    if (flag_set_temp_of_water_warning)
    {
        // 如果要设置水温报警
        flag_set_temp_of_water_warning = 0;
#if USE_MY_DEBUG
        printf(" flag_set_temp_of_water_warning \n");
#endif
        //  发送当前水温报警的状态
        send_data(SEND_TEMP_OF_WATER_ALERT, fun_info.flag_is_in_water_temp_warning);
    }

    if (flag_clear_total_mileage)
    {
        // 如果要清除大计里程
        flag_clear_total_mileage = 0;
        fun_info.save_info.total_mileage = 0;
        distance = 0;
        fun_info_save(); // 将信息写回flash
#if USE_MY_DEBUG
        printf(" flag_clear_total_mileage \n");
#endif
    }

    if (flag_clear_sub_total_mileage)
    {
        // 如果要清除小计里程
        flag_clear_sub_total_mileage = 0;
        fun_info.save_info.subtotal_mileage = 0;
        distance = 0;
        fun_info_save(); // 将信息写回flash
#if USE_MY_DEBUG
        printf(" flag_clear_sub_total_mileage \n");
#endif
    }
}
