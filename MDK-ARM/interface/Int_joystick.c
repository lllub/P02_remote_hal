#include "Int_joystick.h"


uint16_t adc_buffer[4] = {0}; // ADC数据缓冲区 4个通道

/**
 * @brief 初始化ADC摇杆     打开ADC
 * 
 */
void Int_joystick_init(void)
{
    // 直接使用HAL库函数开启ADC
    // 16位数据地址值 其实是32位 32位数据地址值也是32位
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buffer, 4);
}

/**
 * @brief 获取摇杆数据  读取ADC数据 保存到结构体地址
 * 
 * @param joystick 摇杆数据结构体指针
 */
void Int_joystick_get(Joystick_Struct *joystick)
{
    // DMA不依赖CPU计算 -> 读取的数据是实时保存到adc_buffer中的
    // 顺序是自定义的 Rank 1 2 3 4 需对齐
    joystick->thr = adc_buffer[0];
    joystick->yaw = adc_buffer[1];
    joystick->pit = adc_buffer[2];
    joystick->rol = adc_buffer[3];
}
