#include "App_process_data.h"


// 摇杆数据结构体
Joystick_Struct joystick = {0};
// 遥控器数据结构体
Remote_Data remote_data = {0};

// 区分一下摇杆控制值和按键微调值
int16_t key_pit_offset = 0;     // 前正
int16_t key_roll_offset = 0;    // 右正


/**
 * @brief 处理按键数据 => 读取按键状态 进行对应记录
 * 
 */
void App_process_key_data(void)
{
    Key_type key = Int_key_get();
    // 根据key值 进行记录
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
    }
}


/**
 * @brief 处理摇杆数据 => 修正极性相位和标准值
 * 
 */
void App_process_joystick_data(void)
{
    // 获取遥杆数据 -> 获取摇杆监控的ADC值
    Int_joystick_get(&joystick);
    
    //debug_printf("thr = %d, yaw = %d, pit = %d, rol = %d\n", joystick.thr, joystick.yaw, joystick.pit, joystick.rol);
}
