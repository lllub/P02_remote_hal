#include "App_freeRTOS_Task.h"

void task1(void *arg);
// 最小推荐填写128 => 128个32位字节 => 128*4=512字节
#define TASK1_STACK_SIZE 128
// 任务优先级 => 数字越小 优先级越小 => 最大4 => 不推荐使用最小优先级0(系统空闲任务)
#define TASK1_PRIORITY 1
TaskHandle_t task1_handle;

void task2(void *arg);
// 最小推荐填写128 => 128个32位字节 => 128*4=512字节
#define TASK2_STACK_SIZE 128
// 任务优先级 => 数字越小 优先级越小 => 最大4 => 不推荐使用最小优先级0(系统空闲任务)
#define TASK2_PRIORITY 2
TaskHandle_t task2_handle;

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
    xTaskCreate(task1, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &task1_handle);
    xTaskCreate(task2, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &task2_handle);
    // 2. 启动调度器
    vTaskStartScheduler();
}


void task1(void *arg)
{
    // task1的任务启动后 不断执行的内容
    while (1)
    {
        debug_printf("task1 is running...\n");
        // 延时1秒 => 释放CPU占用
        vTaskDelay(1000); 
    }
}

void task2(void *arg)
{
    // task2的任务启动后 不断执行的内容
    while (1)
    {
        debug_printf("task2 is running...\n");
        // 延时1秒 => 释放CPU占用
        vTaskDelay(900); 
    }
}
