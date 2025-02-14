#include "encoder.h"


/* @brief  编码器接口初始化（STM32默认开启，不初始化也可以读编码器值）
 * @param  无参数
 * @retval 无返回值
 */
void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    HAL_TIM_Base_Start_IT(&htim7);
}

/* @brief  读取编码器值，并手动清零
 * @param  Hx: 选择电机编码器H1左上,H2左下,H3右上,H4右下
 * @retval 返回定时器计数值
 */
int16_t Encoder_Read_CNT(uint8_t Hx)
{
    int16_t value;
    switch (Hx) {
        case 1:
            value = __HAL_TIM_GET_COUNTER(&htim2);
            __HAL_TIM_SET_COUNTER(&htim2, 0);
            break;
        case 2:
            value = __HAL_TIM_GET_COUNTER(&htim4);
            __HAL_TIM_SET_COUNTER(&htim4, 0);
            break;
        case 3:
            value = __HAL_TIM_GET_COUNTER(&htim5);
            __HAL_TIM_SET_COUNTER(&htim5, 0);
            break;
        case 4:
            value = __HAL_TIM_GET_COUNTER(&htim3);
            __HAL_TIM_SET_COUNTER(&htim3, 0);
            break;
        default:
            value = 0;
            break;
    }
    return value;
}
