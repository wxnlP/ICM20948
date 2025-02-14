#ifndef __UART_H
#define __UART_H
#include "icm20948.h"

#include <stdlib.h>
#include "usart.h"

void UART_SendInt32(UART_HandleTypeDef *huart, int32_t num);
void UART_SendFloat(UART_HandleTypeDef *huart, float num);
void UART_SendImuData(UART_HandleTypeDef *huart, ImuData data);
#endif //ROBOT_UART_H
