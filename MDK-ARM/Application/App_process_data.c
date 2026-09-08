#include "App_process_data.h"


// 摇杆数据结构体
Joystick_Struct joystick = {0};
// 遥控器数据结构体
Remote_Data remote_data = {0};

// 区分一下摇杆控制值和按键微调值
int16_t key_pit_offset = 0;     // 前正
int16_t key_roll_offset = 0;    // 右正


// 记录摇杆偏移量
int16_t thr_offset = 0;
int16_t yaw_offset = 0;
int16_t pit_offset = 0;
int16_t rol_offset = 0;

//校准摇杆函数
void App_calibrate_joystick(void)
{
    // 零偏校准逻辑 => 减去零偏的值
    // 先清空按键微调值
    key_pit_offset = 0;
    key_roll_offset = 0;
    // 多次读取求平均值
    int16_t thr_sum = 0;
    int16_t yaw_sum = 0;
    int16_t pit_sum = 0;
    int16_t rol_sum = 0;
    for (int i = 0; i < 10; i++)
    {
        App_process_joystick_data();
        thr_sum += joystick.thr - 0;
        yaw_sum += joystick.yaw - 500;
        pit_sum += joystick.pit - 500;
        rol_sum += joystick.rol - 500;
        vTaskDelay(10); // 延时10ms
    }
    // 零偏校准偏移值没有累加效果  会造成两次校准退回的情况
    thr_offset += thr_sum / 10;
    yaw_offset += yaw_sum / 10;
    pit_offset += pit_sum / 10;
    rol_offset += rol_sum / 10;
}


/**
 * @brief 如果freeRTOS两个任务优先级相等 => 两个任务会交替运行
 * 
 */


/**
 * @brief 处理按键数据 => 读取按键状态 进行对应记录
 * 
 */
void App_process_key_data(void)
{
    Key_type key = Int_key_get();
    // 根据key值 进行记录 => 如果进行摇杆校准 => 将按键值调为0 
    if (key == KEY_UP)  
    {
        // 向前飞微调 => 俯仰增加
        key_pit_offset += 10;
    }
    else if (key == KEY_DOWN)
    {
        // 向后飞微调 => 俯仰减少
        key_pit_offset -= 10;
    }
    else if (key == KEY_LEFT)
    {
        // 向左飞微调 => 横滚减少
        key_roll_offset -= 10;
    }
    else if (key == KEY_RIGHT)
    {
        // 向右飞微调 => 横滚增加
        key_roll_offset += 10;
    }
    else if (key == KEY_LEFT_X)
    {
        remote_data.shutdown = 1; // 关机
    }
    else if (key == KEY_RIGHT_X)
    {
        remote_data.fix_height = 1; // 定高
    }
    else if (key == KEY_RIGHT_X_LONG)
    {
        // 校准摇杆
        // 触发校准之后 摇杆值thr为0；yaw，pit，rol为500
        App_calibrate_joystick();
    }
}


/**
 * @brief 处理摇杆数据 => 修正极性相位和标准值
 * 
 */
void App_process_joystick_data(void)
{
    // 解决freeRTOS任务优先级相等的问题 => 任务切换问题
    // 使用临界区解决
    taskENTER_CRITICAL();

    // 1. 获取遥杆数据 -> 获取摇杆监控的ADC值
    Int_joystick_get(&joystick);

    // 2. 处理范围和极性 想要使用的范围值是0-1000 => ADC范围0·4095
    joystick.thr = 1000 - (joystick.thr * 1000 / 4095);
    joystick.yaw = 1000 - (joystick.yaw * 1000 / 4095);
    joystick.pit = 1000 - (joystick.pit * 1000 / 4095);
    joystick.rol = 1000 - (joystick.rol * 1000 / 4095);

    // 3. 处理零偏校准
    joystick.thr -= thr_offset;
    joystick.yaw -= yaw_offset;
    joystick.pit -= pit_offset;
    joystick.rol -= rol_offset;

    // 4. 处理按键微调
    joystick.pit += key_pit_offset;
    joystick.rol += key_roll_offset;


    // 5. 计算偏移值后可能超出范围 => 限制在0-1000
    joystick.thr = Com_limit(joystick.thr, 0, 1000);
    joystick.yaw = Com_limit(joystick.yaw, 0, 1000);
    joystick.pit = Com_limit(joystick.pit, 0, 1000);
    joystick.rol = Com_limit(joystick.rol, 0, 1000);

    // 退出临界区
    taskEXIT_CRITICAL();
    debug_printf(":%d, %d, %d, %d\n", joystick.thr, joystick.yaw, joystick.pit, joystick.rol);
}
