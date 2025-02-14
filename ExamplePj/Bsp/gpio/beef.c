#include "beef.h"
#include "FreeRTOS.h"
#include "task.h"

void Buzzer_Flash(int period)
{
    Buzzer_ON();
//    HAL_Delay(period);
    vTaskDelay(period);
    Buzzer_OFF();
//    HAL_Delay(period);
    vTaskDelay(period);
}

/* 电池警告模块，可通过按键关闭蜂鸣器 */
void Buzzer_ON_Time(void)
{
    static uint8_t status = 1;
    if (status == 1) {
        Buzzer_Flash(100);
    }
    LED_Flash(100);
    if (Key_Status == 0){
        while (Key_Status == 0);
        Buzzer_OFF();
        status = 0;
    }
}



