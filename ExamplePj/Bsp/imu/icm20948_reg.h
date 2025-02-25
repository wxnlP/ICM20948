#ifndef __ICM10948_REG_H
#define __ICM10948_REG_H

/* 读写位 */
#define WRITE                        0x00
#define READ						 0x80
/* ICM20948的从机地址 */
#define ICM20948_ADDRESS             0xD0     // 1101 000
// AD0高电平时的从机地址
#define ICM20948_ADDRESS_AD0         0xD2     // 1101 001
/* ICM20948 USER BANK 0 Registers */
#define ICM20948_WHO_AM_I            0x00
#define ICM20948_USER_CTRL           0x03
#define ICM20948_LP_CONFIG           0x05
#define ICM20948_PWR_MGMT_1          0x06
#define ICM20948_PWR_MGMT_2          0x07
#define ICM20948_INT_PIN_CFG         0x0F
#define ICM20948_INT_ENABLE          0x10
#define ICM20948_INT_ENABLE_1        0x11
#define ICM20948_INT_ENABLE_2        0x12
#define ICM20948_INT_ENABLE_3        0x13
#define ICM20948_I2C_MST_STATUS      0x17
#define ICM20948_INT_STATUS          0x19
#define ICM20948_INT_STATUS_1        0x1A
#define ICM20948_INT_STATUS_2        0x1B
#define ICM20948_INT_STATUS_3        0x1C
#define ICM20948_DELAY_TIME_H        0x28
#define ICM20948_DELAY_TIME_L        0x29
#define ICM20948_ACCEL_XOUT_H        0x2D
#define ICM20948_ACCEL_XOUT_L        0x2E
#define ICM20948_ACCEL_YOUT_H        0x2F
#define ICM20948_ACCEL_YOUT_L        0x30
#define ICM20948_ACCEL_ZOUT_H        0x31
#define ICM20948_ACCEL_ZOUT_L        0x32
#define ICM20948_GYRO_XOUT_H         0x33
#define ICM20948_GYRO_XOUT_L         0x34
#define ICM20948_GYRO_YOUT_H         0x35
#define ICM20948_GYRO_YOUT_L         0x36
#define ICM20948_GYRO_ZOUT_H         0x37
#define ICM20948_GYRO_ZOUT_L         0x38
#define ICM20948_TEMP_OUT_H          0x39
#define ICM20948_TEMP_OUT_L          0x3A
#define ICM20948_EXT_SLV_SENS_DATA_00 0x3B
/* 0x3b~0x52省略 */
#define ICM20948_FIFO_EN_1           0x66
#define ICM20948_FIFO_EN_2           0x67
#define ICM20948_FIFO_RST            0x68
#define ICM20948_FIFO_MODE           0x69
#define ICM20948_FIFO_COUNT          0x70
#define ICM20948_FIFO_R_W            0x72
#define ICM20948_DATA_RDY_STATUS     0x74
#define ICM20948_FIFO_CFG            0x76

/* ICM20948 USER BANK 1 Registers */
#define ICM20948_SELF_TEST_X_GYRO    0x02
#define ICM20948_SELF_TEST_Y_GYRO    0x03
#define ICM20948_SELF_TEST_Z_GYRO    0x04
#define ICM20948_SELF_TEST_X_ACCEL   0x0E
#define ICM20948_SELF_TEST_Y_ACCEL   0x0F
#define ICM20948_SELF_TEST_Z_ACCEL   0x10
#define ICM20948_XA_OFFS_H           0x14
#define ICM20948_XA_OFFS_L           0x15
#define ICM20948_YA_OFFS_H           0x17
#define ICM20948_YA_OFFS_L           0x18
#define ICM20948_ZA_OFFS_H           0x1A
#define ICM20948_ZA_OFFS_L           0x1B
#define ICM20948_TIMEBASE_CORR_PLL   0x28

/* ICM20948 USER BANK 2 Registers */
#define ICM20948_GYRO_SMPLRT_DIV     0x00
#define ICM20948_GYRO_CONFIG_1       0x01
#define ICM20948_GYRO_CONFIG_2       0x02
#define ICM20948_XG_OFFS_USRH        0x03
#define ICM20948_XG_OFFS_USRL        0x04
#define ICM20948_YG_OFFS_USRH        0x05
#define ICM20948_YG_OFFS_USRL        0x06
#define ICM20948_ZG_OFFS_USRH        0x07
#define ICM20948_ZG_OFFS_USRL        0x08
#define ICM20948_ODR_ALIGN_EN        0x09
#define ICM20948_ACCEL_SMPLRT_DIV_1  0x10
#define ICM20948_ACCEL_SMPLRT_DIV_2  0x11
#define ICM20948_ACCEL_INTEL_CTRL    0x12
#define ICM20948_ACCEL_WOM_THR       0x13
#define ICM20948_ACCEL_CONFIG        0x14
#define ICM20948_ACCEL_CONFIG_2      0x15
#define ICM20948_FSYNC_CONFIG        0x52
#define ICM20948_TEMP_CONFIG         0x53
#define ICM20948_MOD_CTRL_USR        0x54

/* ICM20948 USER BANK 3 Registers */
#define ICM20948_I2C_MST_ODR_CFG     0x00
#define ICM20948_I2C_MST_CTRL        0x01
#define ICM20948_I2C_MST_DELAY_CTRL  0x02
#define ICM20948_I2C_SLV0_ADDR       0x03
#define ICM20948_I2C_SLV0_REG        0x04
#define ICM20948_I2C_SLV0_CTRL       0x05
#define ICM20948_I2C_SLV0_DO         0x06
/* 0x07~0x17省略 */

/* To Choose Which Bank */
#define ICM20948_REG_BANK_SEL        0x7F

/* AK09916 Registers */
#define AK09916_ADDRESS              0x0C
#define AK09916_WIA                  0x01 // Who I am, Device ID
#define AK09916_STATUS_1             0x10
#define AK09916_MGTR_XOUTL           0x11
#define AK09916_MGTR_XOUTH           0x12
#define AK09916_MGTR_YOUTL           0x13
#define AK09916_MGTR_YOUTH           0x14
#define AK09916_MGTR_ZOUTL           0x15
#define AK09916_MGTR_ZOUTH           0x16
#define AK09916_STATUS_2             0x18
#define AK09916_CNTL_2               0x31
#define AK09916_CNTL_3               0x32

#endif
