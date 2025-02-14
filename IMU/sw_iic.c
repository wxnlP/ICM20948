#include "sw_iic.h"


// 切换IMU引脚
#define IMU      0

static void delay_us(uint32_t xus)
{
    SysTick->LOAD = 72 * xus;				//设置定时器重装值
    SysTick->VAL = 0x00;					//清空当前计数值
    SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
    while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
    SysTick->CTRL = 0x00000004;				//关闭定时器
}

/* 改变SDA电平 */
static void SDA_Write(uint8_t BitValue)
{
#if IMU == 0
    HAL_GPIO_WritePin(IMU_SDA_GPIO_Port, IMU_SDA_Pin, (GPIO_PinState) BitValue);
#else
    HAL_GPIO_WritePin(IMU1_SDA_GPIO_Port, IMU1_SDA_Pin, ((BitValue) ? GPIO_PIN_SET : GPIO_PIN_RESET));
#endif
//    delay_us(10);
    vTaskDelay(1);
}
/* 改变SCL电平 */
static void SCL_Write(uint8_t BitValue)
{
#if IMU == 0
    HAL_GPIO_WritePin(IMU_SCL_GPIO_Port, IMU_SCL_Pin, (GPIO_PinState) BitValue);
#else
    HAL_GPIO_WritePin(IMU1_SCL_GPIO_Port, IMU1_SCL_Pin, ((BitValue) ? GPIO_PIN_SET : GPIO_PIN_RESET));
#endif
//    delay_us(10);
    vTaskDelay(1);
}
/* 读取SDA电平*/
static GPIO_PinState SDA_Read(void)
{
    GPIO_PinState BitValue;
#if IMU == 0
    BitValue = HAL_GPIO_ReadPin(IMU_SDA_GPIO_Port, IMU_SDA_Pin);
#else
    BitValue = HAL_GPIO_ReadPin(IMU1_SDA_GPIO_Port, IMU1_SDA_Pin);
#endif
//    delay_us(10);
    vTaskDelay(1);
    return BitValue;
}

/* brief: I2C开始条件,SCL高电平期,SDA从高电平切换到低电平
 *
 */
void I2C_Start(void)
{
    // 确保SDA为高电平
    SDA_Write(1);
    // 置SCL为高电平
    SCL_Write(1);
    // 置SDA为低电平,完成下降沿
    SDA_Write(0);
    // 置SCL为低电平,为放数据到SDA上做准备
    SCL_Write(0);
}

/* brief: I2C终止条件,SCL高电平期间,SDA从低电平切换到高电平
 *
 */
void I2C_Stop(void)
{
    // 置SDA为低电平
    SDA_Write(0);
    // 置SCL为低电平
    SCL_Write(1);
    // 确保SDA为高电平,完成上升沿
    SDA_Write(1);
}

/* brief: 发送一个字节,数据位依次放到SDA线上
 * 一个字节 8 bit,所以用uint8_t
 */
void I2C_WriteByte(uint8_t Byte)
{
    uint8_t i;
    for (i=0; i<8; i++)
    {
        // 写数据到SDA
        SDA_Write(Byte & (0x80 >> i));
        // 拉高SCL可以让从机读数据
        SCL_Write(1);
        // 拉低SCL继续发送下一位
        SCL_Write(0);
    }
}

/* brief: 接收一个字节,在SCL高电平期间读取数据位
 * 一个字节 8 bit,所以用uint8_t
 */
uint8_t I2C_ReadByte(void)
{
    uint8_t i, Byte=0x00;
    // 主机释放SDA
    SDA_Write(1);
    for (i=0; i<8; i++)
    {
        // 拉高SCL读数据
        SCL_Write(1);
        // 高电平的位补 1 ，其余不变
        if (SDA_Read() == 1) {Byte |= (0x80 >> i);}
        // 拉低SCL继续发送下一位
        SCL_Write(0);
    }
    return Byte;
}

/* brief: 发送应答
 * 就是发送 1 位数据
 */
void I2C_WriteAcK(uint8_t Ack)
{
    SDA_Write((GPIO_PinState)Ack);
    // 拉高SCL可以让从机读数据
    SCL_Write(1);
    // 拉低SCL继续发送下一位
    SCL_Write(0);
}
/* brief: 接收应答
 * 就是接收 1 位数据
 */
uint8_t I2C_ReceiveAck(void)
{
    uint8_t Ack;
    // 主机释放SDA
    SDA_Write(1);
    // 拉高SCL,读数据
    SCL_Write(1);
    Ack = SDA_Read();
    // 拉低SCL继续发送下一位
    SCL_Write(0);
    return Ack;
}