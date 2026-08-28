#ifndef _INT_KEY_H_
#define _INT_KEY_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"


typedef enum
{
    KEY_NONE = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_LEFT_X,
    KEY_RIGHT_X,
}Key_type;


/**
 * @brief 获取当前按键是否被按下
 * @return 按键类型
 */
Key_type Int_key_get(void);

#endif
