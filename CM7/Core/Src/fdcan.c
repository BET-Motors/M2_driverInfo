/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;
CAN_Internal_State_t state;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */
  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */
  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = ENABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 1;
  hfdcan1.Init.NominalSyncJumpWidth = 1;
  hfdcan1.Init.NominalTimeSeg1 = 41;
  hfdcan1.Init.NominalTimeSeg2 = 38;
  hfdcan1.Init.DataPrescaler = 1;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 1;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.MessageRAMOffset = 0;
  hfdcan1.Init.StdFiltersNbr = 0;
  hfdcan1.Init.ExtFiltersNbr = 1;
  hfdcan1.Init.RxFifo0ElmtsNbr = 32;
  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxFifo1ElmtsNbr = 0;
  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxBuffersNbr = 0;
  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.TxEventsNbr = 0;
  hfdcan1.Init.TxBuffersNbr = 0;
  hfdcan1.Init.TxFifoQueueElmtsNbr = 32;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */

  // --- FILTER CONFIGURATION ---
  // We use one optimized mask to catch all IDs in range 0x10000000 - 0x100000FF
  FDCAN_FilterTypeDef sFilterConfig = {0};

  sFilterConfig.IdType = FDCAN_EXTENDED_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;

  // The Base ID: Matches the prefix of your signals
  sFilterConfig.FilterID1 = 0x10000000;

  // The Mask: Check top 24 bits (0x100000...), ignore last 8 bits
  // This allows IDs 0x10000000 to 0x100000FF to pass.
  sFilterConfig.FilterID2 = 0x1FFFFF00;

  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  // Optional: Reject all Standard Frames explicitly
  HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE);

  // --- START FDCAN ---
  if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }

  // --- ENABLE INTERRUPTS ---
  // Trigger HAL_FDCAN_RxFifo0Callback when a new message arrives
  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE END FDCAN1_Init 2 */

}
/* FDCAN2 init function */
void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */

  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = DISABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = DISABLE;
  hfdcan2.Init.NominalPrescaler = 16;
  hfdcan2.Init.NominalSyncJumpWidth = 1;
  hfdcan2.Init.NominalTimeSeg1 = 1;
  hfdcan2.Init.NominalTimeSeg2 = 1;
  hfdcan2.Init.DataPrescaler = 1;
  hfdcan2.Init.DataSyncJumpWidth = 1;
  hfdcan2.Init.DataTimeSeg1 = 1;
  hfdcan2.Init.DataTimeSeg2 = 1;
  hfdcan2.Init.MessageRAMOffset = 0;
  hfdcan2.Init.StdFiltersNbr = 0;
  hfdcan2.Init.ExtFiltersNbr = 0;
  hfdcan2.Init.RxFifo0ElmtsNbr = 0;
  hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxFifo1ElmtsNbr = 0;
  hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxBuffersNbr = 0;
  hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.TxEventsNbr = 0;
  hfdcan2.Init.TxBuffersNbr = 0;
  hfdcan2.Init.TxFifoQueueElmtsNbr = 0;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */

  /* USER CODE END FDCAN2_Init 2 */

}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED=0;

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */
    /* FDCAN1 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PB9     ------> FDCAN1_TX
    PA11     ------> FDCAN1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
    HAL_NVIC_SetPriority(FDCAN1_IT1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT1_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */

  /* USER CODE END FDCAN1_MspInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspInit 0 */

  /* USER CODE END FDCAN2_MspInit 0 */
    /* FDCAN2 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**FDCAN2 GPIO Configuration
    PB5     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* FDCAN2 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
    HAL_NVIC_SetPriority(FDCAN2_IT1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN2_IT1_IRQn);
  /* USER CODE BEGIN FDCAN2_MspInit 1 */

  /* USER CODE END FDCAN2_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN1 GPIO Configuration
    PB9     ------> FDCAN1_TX
    PA11     ------> FDCAN1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11);

    /* FDCAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
    HAL_NVIC_DisableIRQ(FDCAN1_IT1_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspDeInit 0 */

  /* USER CODE END FDCAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN2 GPIO Configuration
    PB5     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_13);

    /* FDCAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
    HAL_NVIC_DisableIRQ(FDCAN2_IT1_IRQn);
  /* USER CODE BEGIN FDCAN2_MspDeInit 1 */

  /* USER CODE END FDCAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

uint64_t UnpackSignal_(const uint8_t* data, uint8_t startBit, uint8_t length) {
    uint64_t raw64;

    // 1. Use memcpy to prevent alignment crashes on ARM/STM32
    memcpy(&raw64, data, sizeof(uint64_t));

    // 2. Shift (Intel LE standard)
    raw64 >>= startBit;

    // 3. Handle 64-bit length safely (avoiding 1ULL << 64)
    if (length >= 64) {
        return raw64;
    }

    // 4. Mask
    uint64_t mask = (1ULL << length) - 1;
    return raw64 & mask;
}

// Use this for your 8-byte messages
uint64_t UnpackSignal(const uint8_t* data, uint8_t start, uint8_t len) {
    uint64_t val = 0;
    memcpy(&val, data, 8); // Safe 8-byte copy
    val >>= start;
    uint64_t mask = (len >= 64) ? 0xFFFFFFFFFFFFFFFFULL : (1ULL << len) - 1;
    return val & mask;
}

// -----------------------------------------------------------
// Main Rx Task
// -----------------------------------------------------------
void CAN_Dispatcher(uint32_t canId, uint8_t* data) {
    uint64_t rawVal;

    switch (canId) {
        
        case 0x10000004:
            // HV_Voltage (Start: 0, Len: 16)
            rawVal = UnpackSignal(data, 0, 16);
            state.espe.HV_Voltage = (float)rawVal * 0.1f;

            // HV_Current (Start: 16, Len: 16)
            rawVal = UnpackSignal(data, 16, 16);
            state.espe.HV_Current = ((float)rawVal * 0.1f) - 2500.00f;

            // HV_Power (Start: 32, Len: 32)
            rawVal = UnpackSignal(data, 32, 32);
            state.espe.HV_Power = ((float)rawVal * 0.01f) - 2500.00f;

            break;
        case 0x10000005:
            // SOC_Batt_HV (Start: 0, Len: 8)
            rawVal = UnpackSignal(data, 0, 8);
            state.esls2.SOC_Batt_HV = (uint32_t)rawVal;

            // LV_Voltage (Start: 16, Len: 32)
            rawVal = UnpackSignal(data, 16, 32);
            state.esls2.LV_Voltage = (float)rawVal * 0.01f;

            break;
        case 0x10000006:
            // Trq_Act_Wheel_FL (Start: 0, Len: 20)
            rawVal = UnpackSignal(data, 0, 20);
            state.mtc1.Trq_Act_Wheel_FL = ((float)rawVal * 0.1f) - 5000.00f;

            // Trq_Req_Wheel_FL (Start: 32, Len: 20)
            rawVal = UnpackSignal(data, 32, 20);
            state.mtc1.Trq_Req_Wheel_FL = ((float)rawVal * 0.1f) - 5000.00f;

            break;
        case 0x10000007:
            // Trq_Act_Wheel_FR (Start: 0, Len: 20)
            rawVal = UnpackSignal(data, 0, 20);
            state.mtc2.Trq_Act_Wheel_FR = ((float)rawVal * 0.1f) - 5000.00f;

            // Trq_Req_Wheel_FR (Start: 32, Len: 20)
            rawVal = UnpackSignal(data, 32, 20);
            state.mtc2.Trq_Req_Wheel_FR = ((float)rawVal * 0.1f) - 5000.00f;

            break;
        case 0x10000008:
            // Trq_Act_Wheel_RM (Start: 0, Len: 20)
            rawVal = UnpackSignal(data, 0, 20);
            state.mtc3.Trq_Act_Wheel_RM = ((float)rawVal * 0.1f) - 5000.00f;

            // Trq_Req_Wheel_RM (Start: 32, Len: 20)
            rawVal = UnpackSignal(data, 32, 20);
            state.mtc3.Trq_Req_Wheel_RM = ((float)rawVal * 0.1f) - 5000.00f;

            break;
        case 0x10000009:
            // Pwr_Disp (Start: 0, Len: 20)
            rawVal = UnpackSignal(data, 0, 20);
            state.mtc4.Pwr_Disp = ((float)rawVal * 0.01f) - 2500.00f;

            // Trq_Act_Sys (Start: 32, Len: 20)
            rawVal = UnpackSignal(data, 32, 20);
            state.mtc4.Trq_Act_Sys = ((float)rawVal * 0.01f) - 5000.00f;

            break;
        case 0x1000000A:
            // Sys_Eff_Act (Start: 0, Len: 16)
            rawVal = UnpackSignal(data, 0, 16);
            state.ep.Sys_Eff_Act = (float)rawVal * 0.01f;

            // Sys_Eff_Opt (Start: 16, Len: 16)
            rawVal = UnpackSignal(data, 16, 16);
            state.ep.Sys_Eff_Opt = (float)rawVal * 0.01f;

            // LongAccel (Start: 32, Len: 10)
            rawVal = UnpackSignal(data, 32, 10);
            state.ep.LongAccel = (float)rawVal * 0.01f;

            // LatAccel (Start: 48, Len: 10)
            rawVal = UnpackSignal(data, 48, 10);
            state.ep.LatAccel = (float)rawVal * 0.01f;

            break;
        case 0x1000000B:
            // Rng_Rem (Start: 0, Len: 20)
            rawVal = UnpackSignal(data, 0, 20);
            state.ep2.Rng_Rem = (float)rawVal * 0.01f;

            // Rng_Added (Start: 32, Len: 20)
            rawVal = UnpackSignal(data, 32, 20);
            state.ep2.Rng_Added = (float)rawVal * 0.01f;

            break;
        case 0x10000011:
            // VCU_GeneralFaults_1 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_GeneralFaults_1 = (uint64_t)rawVal;

            break;
        case 0x10000012:
            // VCU_GeneralFaults_2 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_GeneralFaults_2 = (uint64_t)rawVal;

            break;
        case 0x10000013:
            // VCU_ComponentFaults_1 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_ComponentFaults_1 = (uint64_t)rawVal;

            break;
        case 0x10000014:
            // VCU_ComponentFaults_2 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_ComponentFaults_2 = (uint64_t)rawVal;

            break;
        case 0x10000015:
            // VCU_ComponentFaults_3 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_ComponentFaults_3 = (uint64_t)rawVal;

            break;
        case 0x10000016:
            // VCU_ComponentFaults_4 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_ComponentFaults_4 = (uint64_t)rawVal;

            break;
        case 0x10000017:
            // VCU_ComponentFaults_5 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_ComponentFaults_5 = (uint64_t)rawVal;

            break;
        case 0x10000018:
            // VCU_ComponentFaults_6 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.faults.VCU_ComponentFaults_6 = (uint64_t)rawVal;

            break;
        case 0x10000019:
            // VCU_GeneralWarnings_1 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_GeneralWarnings_1 = (uint64_t)rawVal;

            break;
        case 0x1000001A:
            // VCU_GeneralWarnings_2 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_GeneralWarnings_2 = (uint64_t)rawVal;

            break;
        case 0x1000001B:
            // VCU_ComponentWarnings_1 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_ComponentWarnings_1 = (uint64_t)rawVal;

            break;
        case 0x1000001C:
            // VCU_ComponentWarnings_2 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_ComponentWarnings_2 = (uint64_t)rawVal;

            break;
        case 0x1000001D:
            // VCU_ComponentWarnings_3 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_ComponentWarnings_3 = (uint64_t)rawVal;

            break;
        case 0x1000001E:
            // VCU_ComponentWarnings_4 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_ComponentWarnings_4 = (uint64_t)rawVal;

            break;
        case 0x1000001F:
            // VCU_ComponentWarnings_5 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_ComponentWarnings_5 = (uint64_t)rawVal;

            break;
        case 0x10000020:
            // VCU_ComponentWarnings_6 (Start: 0, Len: 64)
            rawVal = UnpackSignal(data, 0, 64);
            state.warnings.VCU_ComponentWarnings_6 = (uint64_t)rawVal;

            break;
        case 0x10000021:
            // Pwr_Act_MotRM (Start: 0, Len: 16)
            rawVal = UnpackSignal(data, 0, 16);
            state.pt.Pwr_Act_MotRM = ((float)rawVal * 0.1f) - 2500.00f;

            // Pwr_Act_MotFL (Start: 16, Len: 16)
            rawVal = UnpackSignal(data, 16, 16);
            state.pt.Pwr_Act_MotFL = ((float)rawVal * 0.1f) - 2500.00f;

            // Pwr_Act_MotFR (Start: 32, Len: 16)
            rawVal = UnpackSignal(data, 32, 16);
            state.pt.Pwr_Act_MotFR = ((float)rawVal * 0.1f) - 2500.00f;

            break;
        case 0x10000040:
            // ParkBrake_Status (Start: 0, Len: 3)
            rawVal = UnpackSignal(data, 0, 3);
            state.gbpb.ParkBrake_Status = (uint32_t)rawVal;

            // GearShift_FL_Act_Pos (Start: 4, Len: 3)
            rawVal = UnpackSignal(data, 4, 3);
            state.gbpb.GearShift_FL_Act_Pos = (uint32_t)rawVal;

            // GearShift_FR_Act_Pos (Start: 8, Len: 3)
            rawVal = UnpackSignal(data, 8, 3);
            state.gbpb.GearShift_FR_Act_Pos = (uint32_t)rawVal;

            break;
        case 0x10000043:
            // Odometer (Start: 0, Len: 32)
            rawVal = UnpackSignal(data, 0, 32);
            state.vs1.Odometer = (uint32_t)rawVal;

            // Speed (Start: 32, Len: 12)
            rawVal = UnpackSignal(data, 32, 12);
            state.vs1.Speed = (float)rawVal * 0.1f;

            break;
        default:
            break;
    }
}

void CanRecv(void *args)
{
	FDCAN_RxHeaderTypeDef header;
	uint8_t data[64];
    CAN_Raw_Msg_t rawMsg;
	const uint32_t taskPeriod = 10;
	uint32_t tick = osKernelGetTickCount();

	while(1)
	{
		tick += taskPeriod;
		osDelayUntil(tick);

		while (HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1, FDCAN_RX_FIFO0) > 0)
		{
			if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &header, rawMsg.data) != HAL_OK)
				break;
            
            rawMsg.id = header.Identifier;
            osStatus_t status = osMessageQueuePut(guiMQHandle, &rawMsg, 0, 0);

			CAN_Dispatcher(header.Identifier, rawMsg.data);
		}
		if (HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1, FDCAN_RX_FIFO0) > 0) {
		    osDelay(1);   // give time back deterministically
		}
	}
}

void CAN_GetDriverInputAndVehicleControl(DriverInputAndVehicleControl_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.divc;
    __set_PRIMASK(primask);
}

void CAN_GetDriverInputAndVehicleControl2(DriverInputAndVehicleControl2_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.divc2;
    __set_PRIMASK(primask);
}

void CAN_GetPowertrainStatusAndReadiness(PowertrainStatusAndReadiness_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.ptsr;
    __set_PRIMASK(primask);
}

void CAN_GetElectricalSystemPowerAndEnergy(ElectricalSystemPowerAndEnergy_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.espe;
    __set_PRIMASK(primask);
}

void CAN_GetElectricalSystemLvandsoc2(ElectricalSystemLVAndSOC2_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.esls2;
    __set_PRIMASK(primask);
}

void CAN_GetMotorAndTorqueControl1(MotorAndTorqueControl1_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.mtc1;
    __set_PRIMASK(primask);
}

void CAN_GetMotorAndTorqueControl2(MotorAndTorqueControl2_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.mtc2;
    __set_PRIMASK(primask);
}

void CAN_GetMotorAndTorqueControl3(MotorAndTorqueControl3_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.mtc3;
    __set_PRIMASK(primask);
}

void CAN_GetMotorAndTorqueControl4(MotorAndTorqueControl4_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.mtc4;
    __set_PRIMASK(primask);
}

void CAN_GetEfficiencyAndPerformance(EfficiencyAndPerformance_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.ep;
    __set_PRIMASK(primask);
}

void CAN_GetEfficiencyAndPerformance2(EfficiencyAndPerformance2_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.ep2;
    __set_PRIMASK(primask);
}

void CAN_GetFaults(Faults_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.faults;
    __set_PRIMASK(primask);
}

void CAN_GetWarnings(Warnings_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.warnings;
    __set_PRIMASK(primask);
}

void CAN_GetPowertrain(Powertrain_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.pt;
    __set_PRIMASK(primask);
}

void CAN_GetGearboxAndParkbrake(GearBoxAndParkBrake_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.gbpb;
    __set_PRIMASK(primask);
}

void CAN_GetVehicleState1(VehicleState1_t* out) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    *out = state.vs1;
    __set_PRIMASK(primask);
}
/* USER CODE END 1 */
