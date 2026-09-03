#ifndef __APP_PROCESS_DATA_H__
#define __APP_PROCESS_DATA_H__

#include "Int_joystick.h"
#include "Int_key.h"
#include "Com_debug.h"
#include "Com_tool.h"

/**
 * @brief 遥控器数据结构体
 * 
 */
typedef struct
{
    int16_t thr; // 油门
    int16_t yaw; // 偏航
    int16_t pit; // 俯仰
    int16_t rol; // 横滚
    uint8_t shutdown; // 关机
    uint8_t fix_height; // 定高
}Remote_Data;

/**
 * @brief 处理按键数据 => 读取按键状态 进行对应记录
 * 
 */
void App_process_key_data(void);

/**
 * @brief 处理摇杆数据 => 修正极性相位和标准值
 * 
 */
void App_process_joystick_data(void);

#endif
