#include "pid.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "oled.h"

static PID_Params g_PID = {1.5, 0, 0};
static PID_Error g_Error;
static float g_Target[4] = {0};
static float EncoderMax = 280;

/* 设置目标值 */
void PID_SetTarget(const float* pTarget) {
    for (int i = 0; i < 4; i++) {
        g_Target[i] = pTarget[i];
    }
}

/* 将计算结果运用于控制器 */
static void PID_Func(const float* pDuty) {
    for (int i = 0; i < 4; i++) {
        Motor_SetSpeed(i+1, pDuty[i]);
    }
}

static float PID_EncoderToDuty(int16_t cnt) {
    return (float )(cnt/EncoderMax)*100;
}

/* 获取PID计算结果 */
void PID_Controller(void) {
    float Out[4] = {0};
    char message[100] = "";
    int16_t cnt;
    for (int i = 0; i < 4; i++) {
        cnt = Encoder_Read_CNT(i+1);
        /* 获取真实值 */
        g_Error.Actual = PID_EncoderToDuty(cnt);
        /* 处理误差 */
        g_Error.Pre_Error = g_Error.Cur_Error;
        g_Error.Cur_Error = g_Target[i] - g_Error.Actual;
        g_Error.Cnt_Error += g_Error.Cur_Error;
        /* PID算法 */
        Out[i] = g_PID.P * g_Error.Cur_Error + g_PID.I * g_Error.Cnt_Error + g_PID.D * (g_Error.Cur_Error - g_Error.Pre_Error);
        /* 控制上下限 */
        if ( Out[i] > 100 ) { Out[i] = 100; }
        if ( Out[i] < -100 ) { Out[i] = -100; }
    }
    PID_Func(Out);
    OLED_ShowNum(0, 0, cnt, 5, 16);
    sprintf(message, "%f,%f,%d\r\n", g_Error.Actual, Out[3], 30);
    HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), 100);
}

/* 设置PID参数P */
void PID_SetP(float P) {
    g_PID.P = P;
}

/* 设置PID参数I */
void PID_SetI(float I) {
    g_PID.I = I;
}

/* 设置PID参数D */
void PID_SetD(float D) {
    g_PID.D = D;
}

/* SerialPlot绘图交互 */
void PID_SerialPlot(const float* pDuty, float target, char* message) {
    sprintf(message, "%f,%f,%f,%f,%f\r\n", pDuty[0], pDuty[1], pDuty[2], pDuty[3],target);
    HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), 100);
}