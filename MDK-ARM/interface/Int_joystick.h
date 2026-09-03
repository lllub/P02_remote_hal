#ifndef __INT_JOYSTICK_H__
#define __INT_JOYSTICK_H__

#include "adc.h"

/**
 * @brief 摇杆数据结构体
 */
typedef struct
{
    int16_t thr;    // 油门
    int16_t yaw;    // 偏航
    int16_t pit;    // 俯仰
    int16_t rol;    // 翻滚
} Joystick_Struct;


/**
 * @brief 初始化ADC摇杆     打开ADC
 * 
 */
void Int_joystick_init(void);

/**
 * @brief 获取摇杆数据  读取ADC数据 保存到结构体地址
 * 
 * @param joystick 摇杆数据结构体指针
 */
void Int_joystick_get(Joystick_Struct *joystick);


#endif
