#ifndef __LED_H
#define __LED_H

#include "gpio.h"

#define LED_ON()      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define LED_OFF()     HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)
#define Key_Status    HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)

void LED_Flash(int period);
uint8_t Get_KeyNum(void);

#endif //__LED_H
