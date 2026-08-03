#ifndef COM_DEBUG_H
#define COM_DEBUG_H

#include "usart.h"
#include "stdio.h"
#include "stdarg.h"
#include <string.h>
// 日志输出打印在CPU运行上非常占用资源 => 通过比特率计算打印10字节左右大概需要1ms 非常影响飞机的飞行
// 所以子啊后续飞机需要正常飞行时需要关闭打印功能
// 设计一个日志输出打印开关
#define DEBUG_LOG_ENABLE 1

#ifdef DEBUG_LOG_ENABLE

// 使用宏定义的方式只打印文件名不打印路径名称
// strrchr()从后向前查找字符串中字符
#define __FILE_NAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __FILE_NAME (strrchr(__FILE_NAME__, '/') ? strrchr(__FILE_NAME__, '/') + 1 : __FILE_NAME__)

// 使用宏定义的方式能实现打印日志之前 先添加文件名和行号
#define debug_printf(format, ...) printf("[%s:%d]" format, __FILE_NAME, __LINE__, ##__VA_ARGS__)

#else
// 如果没有开启日志打印 则不做任何处理
#define debug_printf(format, ...)
#endif

#endif /* COM_DEBUG_H */
