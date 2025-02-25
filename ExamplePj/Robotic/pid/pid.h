#ifndef __PID_H
#define __PID_H

#include "motor.h"
#include "encoder.h"

/* PID可调的参数 */
typedef struct {
    float P;
    float I;
    float D;
} PID_Params;

/* PID需从外部获取的参数 */
typedef struct {
    float Cur_Error;
    float Pre_Error;
    float Cnt_Error;
    float Actual;
} PID_Error;


void PID_SetTarget(const float* pTarget);
void PID_Controller(void);
void PID_SetP(float P);
void PID_SetI(float I);
void PID_SetD(float D);
void PID_SerialPlot(const float* pDuty, float target, char* message);

#endif
