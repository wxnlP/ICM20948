/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "beef.h"
#include "oled.h"
#include "icm20948.h"
#include "voltage.h"
#include "can_fd.h"
#include "pid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
        .name = "defaultTask",
        .stack_size = 128 * 4,
        .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void IMU_Task(void *argument);

void RTOS_Init(void);

void CAN_FdTask(void *argument);

void MotorTask(void *arg);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    /* USER CODE BEGIN Init */
    RTOS_Init();
    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    xTaskCreate(IMU_Task, "IMU", 128 * 4, NULL, osPriorityNormal, NULL);
    xTaskCreate(CAN_FdTask, "CAN_FD", 128 * 4, NULL, osPriorityNormal, NULL);
//    xTaskCreate(MotorTask, "Motor", 128 * 4, NULL, osPriorityNormal, NULL);
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument) {
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    ADC_Voltage_Oled();

    /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
// 外设初始
void RTOS_Init(void) {
    OLED_Init();
    ADC_Voltage_Init();
    Motor_Init();
    Encoder_Init();
}

// IMU任务
void IMU_Task(void *argument) {
    ICM20948_Init();
    AK09916_Init();
    ImuAccel accelData;
    ImuGyro gyroData;
    ImuMag magData;
    ImuReal accelReal;
    ImuReal gyroReal;
    ImuReal magReal;
    uint8_t data;
    while (1) {
         data = AK09916_ReadDeviceID();
        OLED_ShowNum(0, 0, data, 3, 16);
        /* 模拟值 */
        ICM20948_ReadGyro(&gyroData);
        ICM20948_ReadAccel(&accelData);
        AK09916_ReadMag(&magData);
        UART_SendImuData(&huart1, &accelData, &gyroData, &magData);
        vTaskDelay(100);
        /* 真实值 */
        ICM20948_RealData(&accelReal, &gyroReal);
        AK09916_RealData(&magReal);
        UART_SendImuReal(&huart1, &accelReal, &gyroReal, &magReal);
        LED_Flash(100);
        vTaskDelay(100);
    }
}

// CAN_FD任务
void CAN_FdTask(void *argument) {
    /* 发�?�部分初始化变量 */
    CAN_TxHeaderTypeDef TxMessage = {
            .StdId = 0x123,
            .ExtId = 0,
            .IDE = CAN_ID_STD, //或CAN_ID_EXT
            .RTR = CAN_RTR_DATA, //或CAN_RTR_REMOTE
            .DLC = 9,
            .TransmitGlobalTime = DISABLE,
    };
    uint8_t TxData[8] = {0x12, 0x98, 0x24, 0x51, 0x00, 0x00, 0x00, 0x00};
    /* 接收部分初始化变�????????????? */
    CAN_RxHeaderTypeDef RxMessage = {0};
    uint8_t RxData[8] = {0};
    /* 显示发�?�循环次�? */
    uint32_t num = 0;
    uint8_t status;
    while (1) {
        /* 发�?�消�? */
        if (Key_Status == 0) {
            status = CAN_SendMessage(&TxMessage, TxData);
            OLED_ShowNum(0, 0, status, 1, 8);
            /* 循环计数 */
            num++;
            vTaskDelay(100);
        }
        /* 接收并显示消�? */
        if (CAN_ReceiveFlag()) {
            status = CAN_ReceiveMessage(&RxMessage, RxData);
            OLED_ShowNum(20, 0, status, 1, 8);
            OLED_ShowNum(0, 1, RxMessage.StdId, 4, 8);
            OLED_ShowNum(20, 1, RxMessage.DLC, 2, 8);
            OLED_ShowNum(40, 1, RxData[0], 3, 8);
            OLED_ShowNum(60, 1, RxData[1], 3, 8);
            OLED_ShowNum(80, 1, RxData[2], 3, 8);
            OLED_ShowNum(100, 1, RxData[3], 3, 8);
        }
        OLED_ShowNum(0, 2, num, 3, 16);
        vTaskDelay(200);
    }
}

void MotorTask(void *arg) {
    TickType_t xLastWakeTime;

    float target[4] = {0, 0, 0, 30};
    PID_SetTarget(target);
//    Motor_SetSpeed(4, 100);
    while (1) {
        xLastWakeTime = xTaskGetTickCount();
//        OLED_ShowNum(0, 0, Encoder_Read_CNT(1), 5, 16);
//        OLED_ShowNum(50, 0, Encoder_Read_CNT(2),5, 16);
//        OLED_ShowNum(0, 2, Encoder_Read_CNT(3), 5, 16);
//        OLED_ShowNum(0, 2, Encoder_Read_CNT(4),5, 16);
//        PID_Controller();
        vTaskDelayUntil(&xLastWakeTime, 10);
    }
}

/* USER CODE END Application */

