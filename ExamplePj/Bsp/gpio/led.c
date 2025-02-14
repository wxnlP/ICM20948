#include "led.h"
#include "FreeRTOS.h"
#include "task.h"

void LED_Flash(int period)
{
    LED_ON();
//    HAL_Delay(period);
    vTaskDelay(period);
    LED_OFF();
//    HAL_Delay(period);
    vTaskDelay(period);
}

uint8_t Get_KeyNum(void)
{
    static uint16_t num=0;
    if (Key_Status == 0)
    {
        while (Key_Status==0);
        num++;
    }
    return num%2;
}