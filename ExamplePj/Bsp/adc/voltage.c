#include "voltage.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

/* @brief  初始化ADC1测量电池电压（连续非扫描模式）
 * @param  无参数
 * @retval 无返回值
 */
void ADC_Voltage_Init(void)
{
    OLED_Init();
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
}

/* @brief  获取ADC模拟值
 * @param  无参数
 * @retval 无返回值
 */
uint16_t ADC_Voltage_Analog(void)
{
    uint16_t value;
    value = HAL_ADC_GetValue(&hadc1);
    return value;
}

/* @brief  获取实际的电压值
 * @param  无参数
 * @retval 无返回值
 */
double ADC_Voltage_Actual(void)
{
    uint16_t value;
    double _voltage, voltage;
    value = ADC_Voltage_Analog();
    _voltage = (value / 4095.0) * 3.30 ;
    voltage = (_voltage / 3.126) * 12.6;
    return voltage;
}

void OLED_ShowVoltage(uint8_t x, uint8_t y, double num, uint8_t fontsize)
{
    uint8_t a = (uint8_t)num % 100;
    uint8_t b = (uint16_t)(num*100) % 100;
    OLED_ShowNum(x, y, a, 2, fontsize);
    OLED_ShowStr(x+fontsize, y, ".", fontsize);
    OLED_ShowNum(x+3*(fontsize/2), y, b, 2, fontsize);
}

/* 电池电压测量函数,串口查看 */
void ADC_Voltage_Uart(void)
{
    uint16_t analog_value = 0;
    double voltage = 0.0;
    char message[25] = "";
    while (1)
    {
        analog_value = ADC_Voltage_Analog();
        voltage = ADC_Voltage_Actual();
        sprintf(message, "ADC: %hu   %.2fV\r\n", analog_value, voltage);
        HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), HAL_MAX_DELAY);
        vTaskDelay(500);
    }
}

/* 电池电压测量函数,OLED查看 */
void ADC_Voltage_Oled(void)
{
    double voltage = 0.0;
    while (1)
    {
        voltage = ADC_Voltage_Actual();
        OLED_ShowVoltage(88, 2, voltage, 16);
        vTaskDelay(500);
    }
}
