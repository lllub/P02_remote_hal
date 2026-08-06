#include "App_freeRTOS_Task.h"

void power_task(void *args);
// 最小推荐填写128 => 128个32位字节 => 128*4=512字节
#define POWER_TASK_STACK_SIZE 128
// 任务优先级 => 数字越小 优先级越小 => 最大4 => 不推荐使用最小优先级0(系统空闲任务)
#define POWER_TASK_PRIORITY 4
TaskHandle_t power_task_handle;

/**
 * @brief  启动freeRTOS操作系统
 */
void App_freeRTOS_start(void)
{
    // 1. 创建任务
    /***
     * @brief  创建任务
     * @param  pxTaskCode: 任务函数指针
     * @param  pcName: 任务名称
     * @param  uxStackDepth: 任务栈大小
     * @param  pvParameters: 传递给任务函数的参数
     * @param  uxPriority: 任务优先级
     * @param  pxCreatedTask: 任务句柄
     */
    
    // 创建电源任务
    xTaskCreate(power_task, "power_task", POWER_TASK_STACK_SIZE, NULL, POWER_TASK_PRIORITY, &power_task_handle);

    // 2. 启动调度器
    vTaskStartScheduler();
}

/**
 * @brief  电源任务
 */
void power_task(void *args)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        // 电源管理任务循环 每10秒执行一次 => 启动电源 避免自动关机
        vTaskDelayUntil(&xLastWakeTime, 10000);     //较vTaskDelay()更精确,有一个基准时间
        // 启动电源
        Int_TP4336_init();
    }
}
