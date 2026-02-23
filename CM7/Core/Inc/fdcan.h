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
/* USER CODE END Includes */

extern FDCAN_HandleTypeDef hfdcan1;

extern FDCAN_HandleTypeDef hfdcan2;

/* USER CODE BEGIN Private defines */

// --------------------------------------------------------
// Consolidated Internal State
// --------------------------------------------------------
typedef struct
{
    // Driver Inputs
    DriverInputAndVehicleControl_t          divc;
    DriverInputAndVehicleControl2_t         divc2;

    // Powertrain Status
    PowertrainStatusAndReadiness_t          ptsr;
    Powertrain_t                            pt;
    GearBoxAndParkBrake_t                   gbpb;

    // Motors & Torque
    MotorAndTorqueControl1_t                mtc1;
    MotorAndTorqueControl2_t                mtc2;
    MotorAndTorqueControl3_t                mtc3;
    MotorAndTorqueControl4_t                mtc4;

    // Electrical System
    ElectricalSystemPowerAndEnergy_t        espe;
    ElectricalSystemLVAndSOC2_t             esls2;

    // Performance & Efficiency
    EfficiencyAndPerformance_t              ep;
    EfficiencyAndPerformance2_t             ep2;

    // Vehicle State
    VehicleState1_t                         vs1;

    // Diagnostics
    Faults_t                                faults;
    Warnings_t                              warnings;

} CAN_Internal_State_t;

void CAN_Dispatcher(uint32_t canId, uint8_t* data);
void CanRecv(void *args);

// --- Getters ---
void CAN_GetDriverInputAndVehicleControl(DriverInputAndVehicleControl_t* out);
void CAN_GetDriverInputAndVehicleControl2(DriverInputAndVehicleControl2_t* out);
void CAN_GetPowertrainStatusAndReadiness(PowertrainStatusAndReadiness_t* out);
void CAN_GetElectricalSystemPowerAndEnergy(ElectricalSystemPowerAndEnergy_t* out);
void CAN_GetElectricalSystemLvandsoc2(ElectricalSystemLVAndSOC2_t* out);
void CAN_GetMotorAndTorqueControl1(MotorAndTorqueControl1_t* out);
void CAN_GetMotorAndTorqueControl2(MotorAndTorqueControl2_t* out);
void CAN_GetMotorAndTorqueControl3(MotorAndTorqueControl3_t* out);
void CAN_GetMotorAndTorqueControl4(MotorAndTorqueControl4_t* out);
void CAN_GetEfficiencyAndPerformance(EfficiencyAndPerformance_t* out);
void CAN_GetEfficiencyAndPerformance2(EfficiencyAndPerformance2_t* out);
void CAN_GetFaults(Faults_t* out);
void CAN_GetWarnings(Warnings_t* out);
void CAN_GetPowertrain(Powertrain_t* out);
void CAN_GetGearboxAndParkbrake(GearBoxAndParkBrake_t* out);
void CAN_GetVehicleState1(VehicleState1_t* out);

/* USER CODE END Private defines */

void MX_FDCAN1_Init(void);
void MX_FDCAN2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __FDCAN_H__ */

