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
#define CAN_ID_MOTOR_AND_TORQUE_CONTROL1            0x10000004
#define CAN_ID_MOTOR_AND_TORQUE_CONTROL2            0x10000005
#define CAN_ID_EFFICIENCY_AND_PERFORMANCE           0x10000006
#define CAN_ID_PRESS_HYDRAULIC_LIGHT_POWERTRAIN     0x10000009
#define CAN_ID_AUXILIARY_STATES_LV_SOC              0x10000011
#define CAN_ID_VEHICLE_STATE_1                      0x10000023

/*
 * CAN Signal Buckets
 * Generated from bucketList.csv
 * Standardized using typedefs.
 */

// Bucket: Driver Input & Vehicle Control
// CAN ID: 0x10000001
typedef struct
{
    uint32_t Acc_Ped_Pos;
    uint32_t Brk_Ped_Pos;
    uint32_t PRND_State; // not showing: Problem on manuelle side
    uint32_t Drv_Program; // VCU side
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

// CAN ID: 0x10000003
typedef struct
{
    uint8_t PT_Ready;
    uint8_t DrvTrain_Status;
    uint8_t MIL_Lamp_Status;
    uint8_t Turn_Indicator_State;
    uint8_t HVDisconnect_Press;
    uint8_t Emergency_Press;
    uint8_t Vehicle_State;
    // add the remaining fields
} PowertrainStatusAndReadiness_t;

// CAN ID: 0x10000009
typedef struct {
    uint8_t Pres_Susp_Front;
    uint8_t Pres_Susp_Rear;
    uint8_t Pres_Brk_Front;
    uint8_t Pres_Brk_Rear;
    uint8_t LowBeam_St;
    uint8_t HighBeam_St;
    uint8_t PosLight_St;
    uint8_t IntLight_St;
    uint16_t Pwr_Act_MotRM;
    uint16_t Pwr_Act_MotFL;
    uint16_t Pwr_Act_MotFR;
} Press_Hydraulic_Light_PowerTrain_t;

// CAN ID: 0x10000004
typedef struct {
    uint16_t Trq_Act_Wheel_FL;
    uint16_t Trq_Req_Wheel_FL;
    uint16_t Trq_Act_Wheel_FR;
    uint16_t Trq_Req_Wheel_FR;
} Motor_And_Torque_Control_1_t;

// CAN ID: 0x10000005
typedef struct { // wrong
    uint16_t Trq_Act_Wheel_RM; // wrong
    uint16_t Trq_Req_Wheel_RM; // wrong
    uint16_t Pwr_Disp;
    uint16_t Trq_Act_Sys;
} Motor_And_Torque_Control_2_t;

// CAN ID: 0x10000006
typedef struct {
    uint32_t Sys_Eff_Act;
    uint32_t Sys_Eff_Opt;
    float LongAccel;
    float LatAccel;
    uint32_t Rng_Rem;
    uint32_t Rng_Added;
} Efficiency_Performance_1_t;

// Bucket: Vehicle State 1
// CAN ID: 0x10000023
typedef struct
{
    uint32_t Odometer;
    float Speed;
    uint8_t RefSpdSens_Direction;
} VehicleState1_t;

typedef struct {
    uint8_t DCDC_State;
    uint8_t AirComp_State;
    uint8_t Heater_State;
    uint8_t HeatPump_State;
    uint8_t SteerByWire_State;
    uint16_t DCDC_HV_Current;
    uint32_t DCDC_HV_Voltage;
    uint32_t SOC_Batt_HV;
    uint32_t LV_Voltage;
} Auxiliary_States_LV_SOC_t;

#ifdef __cplusplus
}
#endif

#endif
