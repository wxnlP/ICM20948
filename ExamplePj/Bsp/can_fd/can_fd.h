#ifndef __CAN_FD_H
#define __CAN_FD_H

#include "can.h"

uint8_t CAN_SendMessage(CAN_TxHeaderTypeDef* TxMessage, uint8_t* pData);
uint8_t CAN_ReceiveFlag(void);
uint8_t CAN_ReceiveMessage(CAN_RxHeaderTypeDef* RxMessage, uint8_t* pData);

#endif
