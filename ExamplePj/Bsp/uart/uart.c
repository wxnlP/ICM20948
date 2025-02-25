#include "uart.h"
#include <stdio.h>
#include <string.h>

// 将整数转换为字符串并通过串口发送
void UART_SendInt32(UART_HandleTypeDef *huart, int32_t num) {
    char str[20];  // 用来存储数字的字符串表示
    int i = 0;
    // 处理负数
    if (num < 0) {
        str[i++] = '-';  // 添加负号
        num = -num;      // 将数字转换为正数
    }
    // 将整数转换为字符串
    sprintf(&str[i], "%ld\r\n", num);  // 将数字转换为字符串
    // 通过串口发送字符串
    HAL_UART_Transmit(huart, (uint8_t*)str, strlen(str), 100);  // 发送字符串
}

// 将浮点数转换为字符串并通过串口发送
void UART_SendFloat(UART_HandleTypeDef *huart, float num) {
    char str[20];  // 存储浮点数的字符串表示，根据需要调整长度
    int i = 0;
    // 处理正负
    if (num < 0) {
        str[i++] = '-';  // 添加负号
        num = -num;  // 取绝对值
    }
    // 将浮点数转换为字符串
    sprintf(&str[i], "%f\r\n", num);  // 将浮点数转换为字符串，保留小数点后 6 位
    // 通过串口发送字符串
    HAL_UART_Transmit(huart, (uint8_t*)str, strlen(str), 100);  // 发送字符串
}

void UART_SendImuData(UART_HandleTypeDef *huart, ImuAccel* accData, ImuGyro* gyroData, ImuMag* magData) {
    static char buffer[64];
    int offset = 0;
    // 使用单次格式化操作（注意防止缓冲区溢出）
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                       "A:%hd,%hd,%hd G:%hd,%hd,%hd M:%hd,%hd,%hd\r\n",  // 格式说明符优化
                       accData->AccX, accData->AccY, accData->AccZ,
                       gyroData->GyroX, gyroData->GyroY, gyroData->GyroZ,
                       magData->MagX, magData->MagY, magData->MagZ);
    // 安全发送（注意：HAL_UART_Transmit需要const uint8_t*）
    if(offset > 0 && offset < sizeof(buffer)){
        HAL_UART_Transmit(huart, (uint8_t*)buffer, offset, 100);
    }
}

void UART_SendImuReal(UART_HandleTypeDef *huart, ImuReal* accData, ImuReal* gyroData, ImuReal* magData) {
    static char buffer[96];
    int offset = 0;
    // 使用单次格式化操作（注意防止缓冲区溢出）
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                       "A_real:%.4f,%.4f,%.4f G_real:%.4f,%.4f,%.4f M_real:%.4f,%.4f,%.4f\r\n",
                       accData->X, accData->Y, accData->Z,
                       gyroData->X, gyroData->Y, gyroData->Z,
                       magData->X, magData->Y, magData->Z);
    // 安全发送（注意：HAL_UART_Transmit需要const uint8_t*）
    if(offset > 0 && offset < sizeof(buffer)){
        HAL_UART_Transmit(huart, (uint8_t*)buffer, offset, 100);
    }
}