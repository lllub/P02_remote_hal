#ifndef __APP_FREERTOS_TASK__
#define __APP_FREERTOS_TASK__

#include "FreeRTOS.h"
#include "task.h"
#include "Com_debug.h"
#include "Int_TP4336.h"
#include "Int_SI24R1.h"
#include "App_process_data.h"
#include "App_transmit_data.h"

/**
 * @brief  启动freeRTOS操作系统
 */
void App_freeRTOS_start(void);

#endif
