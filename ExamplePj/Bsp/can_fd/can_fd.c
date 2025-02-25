#include "can_fd.h"

/**
 * @brief 发送消息
 *
 * @param ID 报文ID
 * @param TxMessage Tx消息头结构体 CAN_TxHeaderTypeDef
 * @param pData 数据指针，可以传入一个数组
 * @retval 1:发送成功; 0:发送失败; -1:Length过大
 * */
uint8_t CAN_SendMessage(CAN_TxHeaderTypeDef* TxMessage, uint8_t* pData) {
    /* 传输数据 */
    // 接收使用的邮箱号
    uint32_t TxMailbox;
    if (HAL_CAN_AddTxMessage(&hcan, TxMessage, pData, &TxMailbox) == HAL_OK) {
        return 1;
    } else {
        return 0;
    }
    /* 等待数据传输完成 */
//    uint32_t timeout = 0;
//    while (HAL_CAN_IsTxMessagePending(&hcan, TxMailbox) != 0) {
//        // 超时退出
//        timeout ++;
//        if (timeout < 10000) {
//            break;
//        }
//    }
}

/**
 * @brief 接收FIFO0邮箱非空标志
 *
 * @retval 1:邮箱非全空; 0:邮箱全空
 * */
uint8_t CAN_ReceiveFlag(void) {
    if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) > 0) {
        return 1;
    }
    return 0;
}

/**
 * @brief 接收消息
 *
 * @param RxMessage Rx消息头结构体 CAN_RxHeaderTypeDef
 * @param pData 将收到的消息的数据存于此变量
 * @retval 无
 * */
uint8_t CAN_ReceiveMessage(CAN_RxHeaderTypeDef* RxMessage, uint8_t* pData) {
    /* 接收数据 */
    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, RxMessage, pData) != HAL_OK) {
        return 0;
    }
    return 1;
}
