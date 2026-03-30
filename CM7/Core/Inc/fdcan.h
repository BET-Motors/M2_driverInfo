/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.h
  * @brief   This file contains all the function prototypes for
  *          the fdcan.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FDCAN_H__
#define __FDCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* USER CODE BEGIN Includes */
#include "betDbc.h"
#include "cmsis_os.h"
/* USER CODE END Includes */

extern FDCAN_HandleTypeDef hfdcan1;

extern FDCAN_HandleTypeDef hfdcan2;

extern osMessageQueueId_t guiMQHandle;

/* USER CODE BEGIN Private defines */

void CanRecv(void *args);

uint64_t UnpackSignal(const uint8_t* data, uint8_t startBit, uint8_t length);
uint64_t UnpackSignalMotorola(const uint8_t* data, uint8_t startbit, uint8_t len);

extern osMessageQueueId_t guiMQHandle;

typedef struct {
    uint32_t id;       // The CAN Identifier (Standard or Extended)
    uint8_t  data[8];  // The 8 bytes of payload data
} CAN_Raw_Msg_t;

/* USER CODE END Private defines */

void MX_FDCAN1_Init(void);
void MX_FDCAN2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __FDCAN_H__ */

