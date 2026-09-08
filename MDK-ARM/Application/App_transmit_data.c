#include "App_transmit_data.h"

extern Remote_Data remote_data;
uint8_t transmit_buff[TX_PLOAD_WIDTH] = {0};
/**
 * @brief 自动切换SI24R1模式 => 将采集完成的遥控器数据打包发送到飞机
 * 
 */
void App_transmit_data(void)
{
    // 1.进入TX模式
    Int_SI24R1_TX_Mode();

    // 2.发送数据 => 唯一性&可靠性  
    // =>（1）帧头校验 指定发送给对应的设备     唯一性
    // =>（2）发送数据结尾 => 添加校验和（将发送的数据累加得到的值添加到数据末尾）  可靠性

    uint32_t checksum = 0;
    // 3字节帧头校验 + 数据本身10字节 + 4字节校验和     17字节
    transmit_buff[0] = FRAME_HEAD_CHECK_1;
    transmit_buff[1] = FRAME_HEAD_CHECK_2;
    transmit_buff[2] = FRAME_HEAD_CHECK_3;
    // 高8位在前
    transmit_buff[3] = (remote_data.thr >> 8) & 0xFF;
    transmit_buff[4] = remote_data.thr & 0xFF;
    transmit_buff[5] = (remote_data.yaw >> 8) & 0xFF;
    transmit_buff[6] = remote_data.yaw & 0xFF;
    transmit_buff[7] = (remote_data.pit >> 8) & 0xFF;
    transmit_buff[8] = remote_data.pit & 0xFF;
    transmit_buff[9] = (remote_data.rol >> 8) & 0xFF;
    transmit_buff[10] = remote_data.rol & 0xFF;
    // 此处的关机和定高只会有0或1的值
    taskENTER_CRITICAL();   // 进入临界区，避免在发送数据的过程中被中断打断，导致关机和定高标志位被修改
    transmit_buff[11] = remote_data.shutdown;
    remote_data.shutdown = 0; // 发送完毕后将关机标志位清零，避免重复发送
    transmit_buff[12] = remote_data.fix_height;
    remote_data.fix_height = 0; // 发送完毕后将定高标志位清零，避免重复发送
    taskEXIT_CRITICAL();
    for (uint8_t i = 0; i < 13; i++)
    {
        checksum += transmit_buff[i];
    }
    // 高位在前
    transmit_buff[13] = (checksum >> 24) & 0xFF;
    transmit_buff[14] = (checksum >> 16) & 0xFF;
    transmit_buff[15] = (checksum >> 8) & 0xFF;
    transmit_buff[16] = checksum & 0xFF;

    Int_SI24R1_TxPacket(transmit_buff);

    // 3. 切换回RX模式
    Int_SI24R1_RX_Mode();
}
