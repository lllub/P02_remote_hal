#include "Int_TP4336.h"

/**
 * @brief  启动TP4336电源 避免自动关机
 */
void Int_TP4336_init(void)
{
    HAL_GPIO_WritePin(POWER_KEY_GPIO_Port, POWER_KEY_Pin, GPIO_PIN_RESET);
    vTaskDelay(100);
    HAL_GPIO_WritePin(POWER_KEY_GPIO_Port, POWER_KEY_Pin, GPIO_PIN_SET);
}
