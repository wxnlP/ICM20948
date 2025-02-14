#ifndef __BEEF_H
#define __BEEF_H

#include "gpio.h"
#include "led.h"

#define Buzzer_ON()   HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)
#define Buzzer_OFF()  HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)

void Buzzer_Flash(int period);
void Buzzer_ON_Time(void);

#endif // __BEEF_H
