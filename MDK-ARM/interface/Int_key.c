#include "Int_key.h"


/**
 * @brief 获取当前按键是否被按下
 * @return 按键类型
 */
Key_type Int_key_get(void)
{
    if (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == GPIO_PIN_RESET)
    {
        // 电弧抖动 => 需要进行消抖
        vTaskDelay(5);
        if (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == GPIO_PIN_RESET)
        {
            // 为不被多层判断 => 等待抬起后返回
            while (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);      // 防止有更低优先级任务被阻塞
            }
            /* key up */
            return KEY_UP;
        }
    }
    else if (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin) == GPIO_PIN_RESET)
    {
        // 电弧抖动 => 需要进行消抖
        vTaskDelay(5);
        if (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin) == GPIO_PIN_RESET)
        {
            // 为不被多层判断 => 等待抬起后返回
            while (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);      // 防止有更低优先级任务被阻塞
            }
            /* key down */
            return KEY_DOWN;
        }
    }
    else if (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin) == GPIO_PIN_RESET)
    {
        // 电弧抖动 => 需要进行消抖
        vTaskDelay(5);
        if (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin) == GPIO_PIN_RESET)
        {
            // 为不被多层判断 => 等待抬起后返回
            while (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);      // 防止有更低优先级任务被阻塞
            }
            /* key left */
            return KEY_LEFT;
        }
    }
    else if (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin) == GPIO_PIN_RESET)
    {
        // 电弧抖动 => 需要进行消抖
        vTaskDelay(5);
        if (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin) == GPIO_PIN_RESET)
        {
            // 为不被多层判断 => 等待抬起后返回
            while (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);      // 防止有更低优先级任务被阻塞
            }
            /* key right */
            return KEY_RIGHT;
        }
    }
    else if (HAL_GPIO_ReadPin(KEY_LEFT_X_GPIO_Port, KEY_LEFT_X_Pin) == GPIO_PIN_RESET)
    {
        // 电弧抖动 => 需要进行消抖
        vTaskDelay(5);
        if (HAL_GPIO_ReadPin(KEY_LEFT_X_GPIO_Port, KEY_LEFT_X_Pin) == GPIO_PIN_RESET)
        {
            // 为不被多层判断 => 等待抬起后返回
            while (HAL_GPIO_ReadPin(KEY_LEFT_X_GPIO_Port, KEY_LEFT_X_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);      // 防止有更低优先级任务被阻塞
            }
            /* key 左上按键被按下 */
            return KEY_LEFT_X;
        }
    }
    else if (HAL_GPIO_ReadPin(KEY_RIGHT_X_GPIO_Port, KEY_RIGHT_X_Pin) == GPIO_PIN_RESET)
    {
        // 开始计时 => 长按为超过1s
        TickType_t count1 = xTaskGetTickCount();
        vTaskDelay(5);
        if(HAL_GPIO_ReadPin(KEY_RIGHT_X_GPIO_Port, KEY_RIGHT_X_Pin) == GPIO_PIN_RESET)
        {
            vTaskDelay(1);      // 防止有更低优先级任务被阻塞
        }
        TickType_t count2 = xTaskGetTickCount();
        if(count2 - count1 > 1000)
        {
            return KEY_RIGHT_X_LONG;
        }
        else
        {
            return KEY_RIGHT_X;
        }
    }
    
    /* none key */
    return KEY_NONE;
}
