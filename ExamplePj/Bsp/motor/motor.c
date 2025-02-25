#include "motor.h"


/* @brief  电机初始化，初始化TIM1和TIM8的PWM信号生成
 * @param  无参数
 * @retval 无返回值
 */
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
}

/* @brief  电机归零，让所以电机停转
 * @param  无参数
 * @retval 无返回值
 */
void Motor_Stop(void)
{
    M1A(0);
    M1B(0);
    M2A(0);
    M2B(0);
    M3A(0);
    M3B(0);
    M4A(0);
    M4B(0);
}

/* @brief  PWM单个电机速度控制
 * @param  Mx: 选择电机M1左上,M2左下,M3右上,M4右下
 * @param  zf: 正反转,1为正转,0为反转
 * @param  duty: 占空比（减去死区后）
 * @retval 无返回值
 */
void Motor_SetSpeed(uint8_t Mx, float duty)
{
    int32_t CompareValue;
    if (Mx < 1 || Mx > 4) return; // 检查电机编号是否有效
    CompareValue = Motor_DutyToCnt(duty);
    switch (Mx) {
        case 1:
            if (CompareValue > 0) {
                M1B(CompareValue);
                M1A(0);
            }
            else {
                M1B(0);
                M1A(-CompareValue);
            }
            break;
        case 2:
            if (CompareValue > 0) {
                M2B(CompareValue);
                M2A(0);
            }
            else {
                M2B(0);
                M2A(-CompareValue);
            }
            break;
        case 3:
            if (CompareValue > 0) {
                M3A(CompareValue);
                M3B(0);
            }
            else {
                M3A(0);
                M3B(-CompareValue);
            }
            break;
        case 4:
            if (CompareValue > 0) {
                M4A(CompareValue);
                M4B(0);
            }
            else {
                M4A(0);
                M4B(-CompareValue);
            }
            break;
        default:
            break;
    }
}

float Motor_CntToDuty(int32_t value) {
    return (100 * ((float)value / (float)(880)));
}

int32_t Motor_DutyToCnt(float duty) {
    if (duty >= 0) {
        return (int32_t)((3600-DEAD_ZONE_ARR) * (fabsf(duty)/100) + DEAD_ZONE_ARR);
    }
    else {
        return -(int32_t)((3600-DEAD_ZONE_ARR) * (fabsf(duty)/100) + DEAD_ZONE_ARR);
    }
}
