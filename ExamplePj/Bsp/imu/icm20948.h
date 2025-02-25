#ifndef __ICM20948_H
#define __ICM20948_H

#include "sw_iic.h"
#include "spi.h"
#include "icm20948_reg.h"

#define SPI

typedef struct {
    int16_t AccX;
    int16_t AccY;
    int16_t AccZ;
} ImuAccel;

typedef struct {
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;
} ImuGyro;

typedef struct {
    int16_t MagX;
    int16_t MagY;
    int16_t MagZ;
} ImuMag;

typedef struct {
    float X;
    float Y;
    float Z;
} ImuReal;

typedef enum
{
    Bank_0 = 0 << 4,
    Bank_1 = 1 << 4,
    Bank_2 = 2 << 4,
    Bank_3 = 3 << 4
} UserBank_t;

#ifdef I2C

void ICM20948_Init(void);
void ICM20948_AckTest(void);
uint8_t ICM20948_ReadDeviceID(void);
void ICM20948_Address_Change(void);
void ICM20948_ReadData(ImuAccel* accData, ImuGyro* gyroData);

#endif

#ifdef SPI

void ICM20948_Init(void);
uint8_t ICM20948_ReadDeviceID(void);
void ICM20948_ReadAccel(ImuAccel* accData);
void ICM20948_ReadGyro(ImuGyro* gyroData);
void ICM20948_RealData(ImuReal* accReal, ImuReal* gyroReal);
void AK09916_Init(void);
uint8_t AK09916_ReadDeviceID(void);
void AK09916_ReadMag(ImuMag* magData);
void AK09916_RealData(ImuReal* magReal);

#endif

#endif
