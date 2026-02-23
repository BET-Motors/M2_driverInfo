#ifndef __BETDBC_H__
#define __BETDBC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

#include <stdint.h>

// ---------------------------------------------------------
// Control & Status Messages
// ---------------------------------------------------------
#define CAN_ID_DRIVER_INPUT_AND_VEHICLE_CONTROL     0x10000001
#define CAN_ID_DRIVER_INPUT_AND_VEHICLE_CONTROL2    0x10000002
#define CAN_ID_POWERTRAIN_STATUS_AND_READINESS      0x10000003
#define CAN_ID_ELECTRICAL_SYSTEM_POWER_AND_ENERGY   0x10000004
#define CAN_ID_ELECTRICAL_SYSTEM_LV_AND_SOC2        0x10000005
#define CAN_ID_MOTOR_AND_TORQUE_CONTROL1            0x10000006
#define CAN_ID_MOTOR_AND_TORQUE_CONTROL2            0x10000007
#define CAN_ID_MOTOR_AND_TORQUE_CONTROL3            0x10000008
#define CAN_ID_MOTOR_AND_TORQUE_CONTROL4            0x10000009
#define CAN_ID_EFFICIENCY_AND_PERFORMANCE           0x1000000A
#define CAN_ID_EFFICIENCY_AND_PERFORMANCE2          0x1000000B
#define CAN_ID_POWERTRAIN                           0x10000021
#define CAN_ID_GEARBOX_AND_PARKBRAKE                0x10000040
#define CAN_ID_VEHICLE_STATE_1                      0x10000043

// ---------------------------------------------------------
// Fault Messages (VCU)
// ---------------------------------------------------------
#define CAN_ID_VCU_GENERALFAULTS_1                  0x10000011
#define CAN_ID_VCU_GENERALFAULTS_2                  0x10000012
#define CAN_ID_VCU_COMPONENTFAULTS_1                0x10000013
#define CAN_ID_VCU_COMPONENTFAULTS_2                0x10000014
#define CAN_ID_VCU_COMPONENTFAULTS_3                0x10000015
#define CAN_ID_VCU_COMPONENTFAULTS_4                0x10000016
#define CAN_ID_VCU_COMPONENTFAULTS_5                0x10000017
#define CAN_ID_VCU_COMPONENTFAULTS_6                0x10000018

// ---------------------------------------------------------
// Warning Messages (VCU)
// ---------------------------------------------------------
#define CAN_ID_VCU_GENERALWARNINGS_1                0x10000019
#define CAN_ID_VCU_GENERALWARNINGS_2                0x1000001A
#define CAN_ID_VCU_COMPONENTWARNINGS_1              0x1000001B
#define CAN_ID_VCU_COMPONENTWARNINGS_2              0x1000001C
#define CAN_ID_VCU_COMPONENTWARNINGS_3              0x1000001D
#define CAN_ID_VCU_COMPONENTWARNINGS_4              0x1000001E
#define CAN_ID_VCU_COMPONENTWARNINGS_5              0x1000001F
#define CAN_ID_VCU_COMPONENTWARNINGS_6              0x10000020

/*
 * CAN Signal Buckets
 * Generated from bucketList.csv
 * Standardized using typedefs.
 */

#include <stdint.h>

// Bucket: Driver Input & Vehicle Control
// CAN ID: 0x10000001
typedef struct
{
    uint32_t Acc_Ped_Pos;
    uint32_t Brk_Ped_Pos;
    uint32_t PRND_State;
    uint32_t Drv_Program;
    float StWhl_Angl_Act;
    float Whl_Angl_Act;
} DriverInputAndVehicleControl_t;

// Bucket: Driver Input & Vehicle Control2
// CAN ID: 0x10000002
typedef struct
{
    uint32_t Sbw_Rack_Pos_Req;
    uint32_t Sbw_Rack_Pos_Act;
} DriverInputAndVehicleControl2_t;

// Bucket: Powertrain Status & Readiness
// CAN ID: 0x10000003
typedef struct
{
    uint32_t PT_Ready;
    uint32_t DrvTrain_Status;
    uint32_t MIL_Lamp_Status;
    uint32_t Turn_Indicator_State;
    uint32_t HVDisconnect_Press;
    uint32_t Emergency_Press;
} PowertrainStatusAndReadiness_t;

// Bucket: Powertrain Status & Readiness
// CAN ID: 0x1000000F

typedef struct {
	uint8_t lowBeam;
	uint8_t highBeam;
	uint8_t posLights;
	uint8_t intLights;
}Lighting_t;

// Bucket: Electrical System - Power & Energy
// CAN ID: 0x10000004
typedef struct
{
    float HV_Voltage;
    float HV_Current;
    float HV_Power;
} ElectricalSystemPowerAndEnergy_t;

// Bucket: Electrical System - LV&SOC2
// CAN ID: 0x10000005
typedef struct
{
    uint32_t SOC_Batt_HV;
    float LV_Voltage;
} ElectricalSystemLVAndSOC2_t;

// Bucket: Motor & Torque Control1
// CAN ID: 0x10000006
typedef struct
{
    float Trq_Act_Wheel_FL;
    float Trq_Req_Wheel_FL;
} MotorAndTorqueControl1_t;

// Bucket: Motor & Torque Control2
// CAN ID: 0x10000007
typedef struct
{
    float Trq_Act_Wheel_FR;
    float Trq_Req_Wheel_FR;
} MotorAndTorqueControl2_t;

// Bucket: Motor & Torque Control3
// CAN ID: 0x10000008
typedef struct
{
    float Trq_Act_Wheel_RM;
    float Trq_Req_Wheel_RM;
} MotorAndTorqueControl3_t;

// Bucket: Motor & Torque Control4
// CAN ID: 0x10000009
typedef struct
{
    float Pwr_Disp;
    float Trq_Act_Sys;
} MotorAndTorqueControl4_t;

// Bucket: Efficiency & Performance
// CAN ID: 0x1000000A
typedef struct
{
    float Sys_Eff_Act;
    float Sys_Eff_Opt;
    float LongAccel;
    float LatAccel;
} EfficiencyAndPerformance_t;

// Bucket: Efficiency & Performance2
// CAN ID: 0x1000000B
typedef struct
{
    float Rng_Rem;
    float Rng_Added;
} EfficiencyAndPerformance2_t;

// Bucket: Faults
// CAN IDs: 0x10000011 - 0x10000018
typedef struct
{
    uint32_t VCU_GeneralFaults_1;
    uint32_t VCU_GeneralFaults_2;
    uint32_t VCU_ComponentFaults_1;
    uint32_t VCU_ComponentFaults_2;
    uint32_t VCU_ComponentFaults_3;
    uint32_t VCU_ComponentFaults_4;
    uint32_t VCU_ComponentFaults_5;
    uint32_t VCU_ComponentFaults_6;
} Faults_t;

// Bucket: Warnings
// CAN IDs: 0x10000019 - 0x10000020
typedef struct
{
    uint32_t VCU_GeneralWarnings_1;
    uint32_t VCU_GeneralWarnings_2;
    uint32_t VCU_ComponentWarnings_1;
    uint32_t VCU_ComponentWarnings_2;
    uint32_t VCU_ComponentWarnings_3;
    uint32_t VCU_ComponentWarnings_4;
    uint32_t VCU_ComponentWarnings_5;
    uint32_t VCU_ComponentWarnings_6;
} Warnings_t;

// Bucket: Powertrain
// CAN ID: 0x10000021
typedef struct
{
    uint32_t Pwr_Act_MotRM;
    uint32_t Pwr_Act_MotFL;
    uint32_t Pwr_Act_MotFR;
} Powertrain_t;

// Bucket: GearBox & ParkBrake
// CAN ID: 0x10000040
typedef struct
{
    uint32_t ParkBrake_Status;
    uint32_t GearShift_FL_Act_Pos;
    uint32_t GearShift_FR_Act_Pos;
} GearBoxAndParkBrake_t;

// Bucket: Vehicle State 1
// CAN ID: 0x10000043
typedef struct
{
    uint32_t Odometer;
    float Speed;
} VehicleState1_t;


#ifdef __cplusplus
}
#endif

#endif
