#ifndef __ICM20948_H
#define __ICM20948_H

#include "sw_iic.h"
#include "icm10948_reg.h"

typedef struct {
    int16_t AccX;
    int16_t AccY;
    int16_t AccZ;
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;
} ImuData;


void ICM20948_Init(void);
void AK09916_Init(void);
uint8_t ICM20948_ReadDeviceID(void);
uint8_t AK09916_ReadDeviceID(void);
void ICM20948_Address_Change(void);
void ICM20948_ReadData(ImuData* data);
void ICM20948_AckTest(void);

#endif
