#ifndef __VOLTAGE_H
#define __VOLTAGE_H
#include "adc.h"
#include "uart.h"
#include "oled.h"

void ADC_Voltage_Init(void);
uint16_t ADC_Voltage_Analog(void);
double ADC_Voltage_Actual(void);
void OLED_ShowVoltage(uint8_t x, uint8_t y, double num, uint8_t fontsize);
void ADC_Voltage_Oled(void);
void ADC_Voltage_Uart(void);
#endif //ROBOT_VOLTAGE_H
