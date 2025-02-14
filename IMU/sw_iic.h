#ifndef __SW_IIC_H
#define __SW_IIC_H

#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"

void I2C_Start(void);
void I2C_Stop(void);
void I2C_WriteByte(uint8_t Byte);
uint8_t I2C_ReadByte(void);
void I2C_WriteAcK(uint8_t Ack);
uint8_t I2C_ReceiveAck(void);


#endif //SW_I2C_SWI2C_H
