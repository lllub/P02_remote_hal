#include "App_freeRTOS_Task.h"

// STM32F103C8T6 => SRAM 20K => 分配12K给操作系统

// 电源管理任务
void power_task(void *args);
// 最小推荐填写128 => 128个32位字节 => 128*4=512字节
#define POWER_TASK_STACK_SIZE 128
// 任务优先级 => 数字越小 优先级越小 => 最大4 => 不推荐使用最小优先级0(系统空闲任务)
#define POWER_TASK_PRIORITY 4
TaskHandle_t power_task_handle;
#define POWER_TASK_PERIOD 10000


// 通讯任务
void com_task(void *args);
#define COM_TASK_STACK_SIZE 128
#define COM_TASK_PRIORITY 3
TaskHandle_t com_task_handle;
// 任务周期
#define COM_TASK_PERIOD 6


// 按键任务
void key_task(void *args);
#define KEY_TASK_STACK_SIZE 128
#define KEY_TASK_PRIORITY 2
TaskHandle_t key_task_handle;
// 任务周期
#define KEY_TASK_PERIOD 20


// 摇杆任务
void joystick_task(void *args);
#define JOYSTICK_TASK_STACK_SIZE 128
#define JOYSTICK_TASK_PRIORITY 2
TaskHandle_t joystick_task_handle;
//任务周期
#define JOYSTICK_TASK_PERIOD 20


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
    
    // 1.创建电源任务
    xTaskCreate(power_task, "power_task", POWER_TASK_STACK_SIZE, NULL, POWER_TASK_PRIORITY, &power_task_handle);

    // 2.创建通讯任务
    xTaskCreate(com_task, "com_task", COM_TASK_STACK_SIZE, NULL, COM_TASK_PRIORITY, &com_task_handle);

    // 3.创建按键任务
    xTaskCreate(key_task, "key_task", KEY_TASK_STACK_SIZE, NULL, KEY_TASK_PRIORITY, &key_task_handle);

    // 4.创建摇杆任务
    xTaskCreate(joystick_task, "joystick_task", JOYSTICK_TASK_STACK_SIZE, NULL, JOYSTICK_TASK_PRIORITY, &joystick_task_handle);

    // 启动调度器
    vTaskStartScheduler();
}

/**
 * @brief  电源任务
 */
void power_task(void *args)
{
    // 获取当前的基准时间
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        // 电源管理任务循环 每10秒执行一次 => 启动电源 避免自动关机
        vTaskDelayUntil(&xLastWakeTime, POWER_TASK_PERIOD);     //较vTaskDelay()更精确,有一个基准时间
        // 启动电源
        Int_TP4336_init();
    }
}

/**
 * @brief  摇杆任务
 */
void joystick_task(void *args)
{
    // 获取当前的基准时间
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // 初始化遥杆ADC
    Int_joystick_init();
    while (1)
    {
        // 统一处理方式 => 应用层处理
        App_process_joystick_data();
        
        // 20ms执行一次
        vTaskDelayUntil(&xLastWakeTime, JOYSTICK_TASK_PERIOD);
    }
}

/**
 * @brief  按键任务
 */
void key_task(void *args)
{
    // 获取当前的基准时间
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        // 统一处理方式 => 应用层处理
        App_process_key_data();
        
        // 20ms执行一次
        vTaskDelayUntil(&xLastWakeTime, KEY_TASK_PERIOD);
    }
}


uint8_t com_buff[TX_PLOAD_WIDTH] = {0};
/**
 * @brief  通讯任务
 */
void com_task(void *args)
{
    // 获取当前的基准时间
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        // 调用SI24R1接口 发送数据
        // 1.进入TX模式
        Int_SI24R1_TX_Mode();
        // 2.发送数据

        // 测试用数据
        com_buff[0] = 'h';
        com_buff[1] = 'e';
        com_buff[2] = 'l';
        com_buff[3] = 'l';
        com_buff[4] = 'o';
        com_buff[5] = '!';

        Int_SI24R1_TxPacket(com_buff);
        // 3.恢复RX模式
        Int_SI24R1_RX_Mode();
        // 6ms执行一次
        vTaskDelayUntil(&xLastWakeTime, COM_TASK_PERIOD);

    }
}
