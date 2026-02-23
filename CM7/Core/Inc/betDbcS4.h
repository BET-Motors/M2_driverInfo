#ifndef __BETDBCS4_H__
#define __BETDBCS4_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

#include <stdint.h>

// ---------------------------------------------------------
// Messages
// ---------------------------------------------------------
#define CAN_ID_AIR_COMPRESSOR_SYSTEM                    0x1000002F
#define CAN_ID_AUXILARIE_STATES                         0x10000030
#define CAN_ID_BMS_VALUES_1                             0x10000031
#define CAN_ID_BMS_VALUES_2                             0x10000032
#define CAN_ID_BMS_VALUES_3_1                           0x10000033
#define CAN_ID_BMS_VALUES_3_2                           0x10000040
#define CAN_ID_DRIVER_INPUT_TX                          0x00001001
#define CAN_ID_FUSEBOX1                                 0x10000023
#define CAN_ID_PNEUMATICSYSTEM_TX_1                     0x00001007
#define CAN_ID_PNEUMATICSYSTEM_TX_2                     0x1000000E
#define CAN_ID_RELAY_FUSEBOX_CONTROL_TX                 0x00001006
#define CAN_ID_THERMAL_MANAGEMENT_1_TX                  0x00001003
#define CAN_ID_THERMAL_MANAGEMENT_2_TX                  0x00001004

/*
 * CAN Signal Buckets
 * Generated from bucketList_screens4.csv
 * Standardized using typedefs.
 */

// Bucket: Air Compressor System
// CAN ID: 0x1000002F
typedef struct
{
    uint32_t Airc_speed;
    uint32_t Airc_traction_voltage;
    float Airc_torque;
    float Airc_power;
} AirCompressorSystem_t;

// Bucket: Auxilarie States
// CAN ID: 0x10000030
typedef struct
{
    uint32_t DCDC_State;
    uint32_t AirComp_State;
    uint32_t Heater_State;
    uint32_t HeatPump_State;
    uint32_t SteerByWire_State;
    float DCDC_HV_Current;
    uint32_t DCDC_HV_Voltage;
} AuxilarieStates_t;

// Bucket: BMS Values 1
// CAN ID: 0x10000031
typedef struct
{
    float BMS_Max_DischargeCurrentCont;
    float BMS_Max_DischargeCurrentPeak;
    float BMS_Max_ChargeCurrentCont;
    float BMS_Max_ChargeCurrentPeak;
} BMSValues1_t;

// Bucket: BMS Values 2
// CAN ID: 0x10000032
typedef struct
{
    uint32_t BMS_InsulationValue;
} BMSValues2_t;

// Bucket: BMS Values 3
// CAN ID: 0x10000033, 0x10000040
typedef struct
{
    float BMS_LV_SupplyVolt;
    uint32_t BMS_Dsg_ContS1_FB;
    uint32_t BMS_Dsg_ContS2_FB;
    uint32_t BMS_HVIL_FB;
    uint32_t BMS_PreCharge_Cont_FB;
    uint32_t BMS_Status;
    uint32_t BMS_FaultLevel;
    uint32_t GearBoxFrontOilPumps_Status;
    uint32_t SuctionPump_Rear_Status;
    uint32_t SuctionPump_Front_Status;
} BMSValues3_t;

// Bucket: Driver Input TX
// CAN ID: 0x00001001
typedef struct
{
    uint32_t Drv_Program_Sw;
    uint32_t Override_Req;
    uint32_t Gear_Actuator_Override;
    uint32_t Level_Control_Req;
    uint32_t DCDC_Req;
} DriverInputTX_t;

// Bucket: FuseBox1
// CAN ID: 0x10000023
typedef struct
{
    uint32_t FuseBox1_State_Relay_1_8;
} FuseBox1_t;

// Bucket: PneumaticSystem TX
// CAN ID: 0x00001007, 0x1000000E
typedef struct
{
    uint32_t AirCompressor_Req;
    float MinPressureAir;
    float MaxPressureAir;
    uint32_t Rad_Fan_Speed;
} PneumaticSystemTX_t;

// Bucket: Relay&FuseBox Control TX
// CAN ID: 0x00001006
typedef struct
{
    uint32_t Box1_Req;
    uint32_t Box2_Req;
} RelayFuseBoxControlTX_t;

// Bucket: Thermal Management 1 TX
// CAN ID: 0x00001003
typedef struct
{
    uint32_t HVHeaterEnable;
    uint32_t HVHeater_TargetCoolantTemp;
    uint32_t HeatPump_Req;
    uint32_t HeatFoil_Req;
    uint32_t LVvalve1_Req;
    uint32_t LVvalve2_Req;
    uint32_t LVvalve3_Req;
} ThermalManagement1TX_t;

// Bucket: Thermal Management 2 TX
// CAN ID: 0x00001004
typedef struct
{
    uint32_t LowerLimit_HeatPump;
    uint32_t UpperLimit_HeatPump;
    uint32_t UpperLimit_ActiveHeatup;
} ThermalManagement2TX_t;


#ifdef __cplusplus
}
#endif

#endif
