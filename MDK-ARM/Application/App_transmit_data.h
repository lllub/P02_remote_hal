#ifndef __APP_TRANSMIT_DATA_H
#define __APP_TRANSMIT_DATA_H

#include "Int_SI24R1.h"
#include "App_process_data.h"
#include "FreeRTOS.h"
#include "task.h"

// 定义帧头校验的值
#define FRAME_HEAD_CHECK_1 'l'
#define FRAME_HEAD_CHECK_2 'y'
#define FRAME_HEAD_CHECK_3 'b'


/**
 * @brief 自动切换SI24R1模式 => 将采集完成的遥控器数据打包发送到飞机
 * 
 */
void App_transmit_data(void);

#endif
