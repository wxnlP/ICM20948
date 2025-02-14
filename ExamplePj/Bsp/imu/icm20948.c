#include "icm20948.h"
#include "oled.h"


#define I2C

#ifdef I2C

static void ICM20948_WriteByte(uint8_t SlaveAddress, uint8_t RegisterAddress, uint8_t RegisterData) {
    I2C_Start();
    I2C_WriteByte(SlaveAddress|0x00);
    I2C_ReceiveAck();
    I2C_WriteByte(RegisterAddress);
    I2C_ReceiveAck();
    I2C_WriteByte(RegisterData);
    I2C_ReceiveAck();
    I2C_Stop();
}


static uint8_t ICM20948_ReadByte(uint8_t SlaveAddress, uint8_t RegisterAddress) {
    uint8_t RegisterData;
    I2C_Start();
    I2C_WriteByte(SlaveAddress|0x00);
    I2C_ReceiveAck();
    I2C_WriteByte(RegisterAddress);
    I2C_ReceiveAck();

    I2C_Start();
    I2C_WriteByte(SlaveAddress|0x01);
    I2C_ReceiveAck();
    RegisterData = I2C_ReadByte();
    I2C_WriteAcK(1);
    I2C_Stop();
    return RegisterData;
}

#endif
#ifdef SPI
static void ICM20948_WriteByte(uint8_t RegisterAddress, uint8_t RegisterData) {
    SPI_Start();
    /* 发送读指令和寄存器地址 */
    SPI_SwapByte(0x00|RegisterAddress);
    /* 发送数据 */
    SPI_SwapByte(RegisterData);
}

static uint8_t ICM20948_ReadByte(uint8_t RegisterAddress) {
    uint8_t value;
    /* 开始SPI */
    SPI_Start();
    /* 发送读指令和寄存器地址 */
    SPI_SwapByte(0x80|RegisterAddress);
    /* 接收数据数据 */
    value = SPI_SwapByte(0xFF);
    /* 结束SPI */
    SPI_Stop();
    return value;
}
#endif

#ifdef HW_SPI
static void ICM20948_Enable(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

static void ICM20948_Disable(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

static void ICM20948_WriteByte(uint8_t RegisterAddress, uint8_t RegisterData) {
    ICM20948_Enable();
    /* 发送读指令和寄存器地址 */
    HAL_SPI_Transmit(&hspi2, (uint8_t *) (0x00 | RegisterAddress), 1, 1000);
    /* 发送数据 */
    HAL_SPI_Transmit(&hspi2, &RegisterData, 1, 1000);
    ICM20948_Disable();
}

static uint8_t ICM20948_ReadByte(uint8_t RegisterAddress) {
    uint8_t value;
    /* 开始SPI */
    ICM20948_Enable();
    /* 发送读指令和寄存器地址 */
    HAL_SPI_Transmit(&hspi2, (uint8_t *) (0x80 | RegisterAddress), 1, 1000);
    /* 接收数据数据 */
    HAL_SPI_Receive(&hspi2, &value, 1, 1000);
    /* 结束SPI */
    ICM20948_Disable();
    return value;
}
#endif

/* 切换寄存器BANK */
static void ICM20948_SelectBank(uint8_t BankX) {
    switch (BankX) {
        case 0:
            /* 0000 0000 */
            ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_REG_BANK_SEL, 0x00);
            break;
        case 1:
            /* 0001 0000 */
            ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_REG_BANK_SEL, 0x10);
            break;
        case 2:
            /* 0010 0000 */
            ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_REG_BANK_SEL, 0x20);
            break;
        case 3:
            /* 0011 0000 */
            ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_REG_BANK_SEL, 0x30);
            break;
        default:
            ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_REG_BANK_SEL, 0x00);
    }
}

/* ICM20948初始化 */
void ICM20948_Init(void) {
    /* BANK 0 */
    /* 选择bank0 */
    ICM20948_SelectBank(0);
    /* 复位寄存器,取消睡眠模式 */
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_PWR_MGMT_1, 0x80);
    vTaskDelay(100);
    /* 自动选择合适的时钟源 */
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_PWR_MGMT_1, 0x01);
    /* 开启陀螺仪和加速度计的所有轴 */
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_PWR_MGMT_2, 0x00);
    /* BANK 1 NONE */
    /* BANK 2 */
    /* 选择bank2 */
    ICM20948_SelectBank(2);
    /* 配置陀螺仪采样频率 1.1kHZ/(0x04+1) = 220HZ */
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_GYRO_SMPLRT_DIV, 0x04);
    /* 陀螺仪Config,使用DLPF(低通滤波),DLPFCFG=3,设置量程为 ±2000dps */
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_GYRO_CONFIG_1, 0x1F);
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_GYRO_CONFIG_2, 0x00);
    /* 配置加速度计采样频率 1.125kHZ/(0x000A+1) = 102HZ */
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_ACCEL_SMPLRT_DIV_1, 0x00);
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_ACCEL_SMPLRT_DIV_2, 0x0A);
    /* 加速度计Config,使用DLPF(低通滤波),DLPFCFG=3,设置量程为 ±8g */
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_ACCEL_CONFIG, 0x1D);
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_ACCEL_CONFIG_2, 0x00);
    /* BANK 3 NONE */
}

/* 磁力计初始化(待测试) */
void AK09916_Init(void) {
    ICM20948_SelectBank(0);
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_USER_CTRL, 0x00);
    ICM20948_WriteByte(ICM20948_ADDRESS, ICM20948_INT_PIN_CFG, 0x82);
}

/* IMU单元应答测试 */
void ICM20948_AckTest(void) {
    uint8_t ack;
    I2C_Start();
    I2C_WriteByte(0xD0);
    ack = I2C_ReceiveAck();
    I2C_Stop();
    OLED_ShowNum(0, 0, ack, 1, 16);
}

uint8_t ICM20948_ReadDeviceID(void) {
    ICM20948_SelectBank(0);
    return ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_WHO_AM_I);
}

uint8_t AK09916_ReadDeviceID(void) {
//    ICM20948_SelectBank(0);
    return ICM20948_ReadByte(AK09916_ADDRESS, AK09916_WIA);
}

void ICM20948_Address_Change(void) {
    HAL_GPIO_WritePin(IMU_AD0_GPIO_Port, IMU_AD0_Pin, GPIO_PIN_SET);
}

/* 读取加速度计、陀螺仪数据 */
void ICM20948_ReadData(ImuData* data) {
    /* 加速度真实值: 寄存器值/4095 ; 4095 = 65535/16 = 16位ADC/量程
     * 角速度真实值: 寄存器值/16.4 ; 16.4 = 65535/4000 = 16位ADC/量程
     * */
    ICM20948_SelectBank(0);
    uint8_t accX_H = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_ACCEL_XOUT_H);
    uint8_t accX_L = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_ACCEL_XOUT_L);
    data->AccX = ((accX_H << 8) | accX_L);

    uint8_t accY_H = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_ACCEL_YOUT_H);
    uint8_t accY_L = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_ACCEL_YOUT_L);
    data->AccY = ((accY_H << 8) | accY_L);

    uint8_t accZ_H = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_ACCEL_ZOUT_H);
    uint8_t accZ_L = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_ACCEL_ZOUT_L);
    data->AccZ = ((accZ_H << 8) | accZ_L);

    uint8_t GyroX_H = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_GYRO_XOUT_H);
    uint8_t GyroX_L = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_GYRO_XOUT_L);
    data->GyroX = ((GyroX_H << 8) | GyroX_L);

    uint8_t GyroY_H = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_GYRO_YOUT_H);
    uint8_t GyroY_L = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_GYRO_YOUT_L);
    data->GyroY = ((GyroY_H << 8) | GyroY_L);

    uint8_t GyroZ_H = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_GYRO_ZOUT_H);
    uint8_t GyroZ_L = ICM20948_ReadByte(ICM20948_ADDRESS, ICM20948_GYRO_ZOUT_L);
    data->GyroZ = ((GyroZ_H << 8) | GyroZ_L);
}


