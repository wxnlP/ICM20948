#ifndef __MOTOR_H
#define __MOTOR_H

#include "tim.h"
#include <math.h>


void Motor_Init(void);
void Motor_Stop(void);
void Motor_SetSpeed(uint8_t Mx, float duty);
float Motor_CntToDuty(int32_t value);
int32_t Motor_DutyToCnt(float duty);

// 定义死区阈值（占空比），最低的比较值为1800
#define DEAD_ZONE_THRESHOLD     50.0
#define DEAD_ZONE_ARR           1800
#define M1A(duty)               __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, duty)
#define M1B(duty)               __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, duty)
#define M2A(duty)               __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, duty)
#define M2B(duty)               __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, duty)
#define M3A(duty)               __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, duty)
#define M3B(duty)               __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, duty)
#define M4A(duty)               __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, duty)
#define M4B(duty)               __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, duty)

#endif //ROBOT_MOTOR_H
