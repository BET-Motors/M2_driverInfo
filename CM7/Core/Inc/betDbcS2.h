#ifndef __BETDBCS2_H__
#define __BETDBCS2_H__

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
#define CAN_ID_BMS_VALUES_10                            0x1000003A
#define CAN_ID_BMS_VALUES_11                            0x1000003B
#define CAN_ID_BMS_VALUES_12                            0x1000003C
#define CAN_ID_BMS_VALUES_13                            0x1000003D
#define CAN_ID_BMS_VALUES_14                            0x1000003E
#define CAN_ID_BMS_VALUES_15                            0x1000003F
#define CAN_ID_BMS_VALUES_6                             0x10000036
#define CAN_ID_BMS_VALUES_7                             0x10000037
#define CAN_ID_BMS_VALUES_8                             0x10000038
#define CAN_ID_BMS_VALUES_9                             0x10000039
#define CAN_ID_ELECTRICAL_SYSTEM_POWER_ENERGY2_1        0x10000022
#define CAN_ID_ELECTRICAL_SYSTEM_POWER_ENERGY2_2        0x10000024
#define CAN_ID_ELECTRICAL_SYSTEM_POWER_ENERGY2_3        0x10000025
#define CAN_ID_ELECTRICAL_SYSTEM_POWER_ENERGY2_4        0x10000026
#define CAN_ID_ELECTRICAL_SYSTEM_POWER_ENERGY2_5        0x10000027
#define CAN_ID_ELECTRICAL_SYSTEM_POWER_ENERGY2_6        0x10000028
#define CAN_ID_FUSEBOX2_1                               0x10000029
#define CAN_ID_FUSEBOX2_2                               0x1000002A
#define CAN_ID_FUSEBOX2_3                               0x1000002B
#define CAN_ID_FUSEBOX2_4                               0x1000002C
#define CAN_ID_FUSEBOX2_5                               0x1000002D
#define CAN_ID_FUSEBOX2_6                               0x1000002E
#define CAN_ID_FUSEBOX2_7                               0x10000035
#define CAN_ID_GEARBOX_TEMPERATURES_1                   0x10000041
#define CAN_ID_GEARBOX_TEMPERATURES_2                   0x10000042
#define CAN_ID_LIGHTING_SYSTEMS_TX                      0x00001002
#define CAN_ID_PRESSURE_HYDRAULIC_SYSTEMS               0x10000010
#define CAN_ID_THERMAL_MANAGEMENT                       0x1000000C
#define CAN_ID_THERMAL_MANAGEMENT2                      0x1000000D
#define CAN_ID_THERMAL_MANAGEMENT3                      0x1000000E

/*
 * CAN Signal Buckets
 * Generated from bucketList_screens2.csv
 * Standardized using typedefs.
 */

// Bucket: BMS Values 10
// CAN ID: 0x1000003A
typedef struct
{
    float BMS_M11_Temp_max;
    float BMS_M11_Temp_min;
    float BMS_M12_Temp_max;
    float BMS_M12_Temp_min;
    float BMS_M13_Temp_max;
} BMSValues10_t;

// Bucket: BMS Values 11
// CAN ID: 0x1000003B
typedef struct
{
    float BMS_M13_Temp_min;
    float BMS_M14_Temp_max;
    float BMS_M14_Temp_min;
    float BMS_M15_Temp_max;
    float BMS_M15_Temp_min;
} BMSValues11_t;

// Bucket: BMS Values 12
// CAN ID: 0x1000003C
typedef struct
{
    float BMS_M16_Temp_max;
    float BMS_M16_Temp_min;
    float BMS_M17_Temp_max;
    float BMS_M17_Temp_min;
    float BMS_M18_Temp_max;
} BMSValues12_t;

// Bucket: BMS Values 13
// CAN ID: 0x1000003D
typedef struct
{
    float BMS_M18_Temp_min;
    float BMS_M19_Temp_max;
    float BMS_M19_Temp_min;
    float BMS_M20_Temp_max;
    float BMS_M20_Temp_min;
} BMSValues13_t;

// Bucket: BMS Values 14
// CAN ID: 0x1000003E
typedef struct
{
    float BMS_M21_Temp_max;
    float BMS_M21_Temp_min;
    float BMS_M22_Temp_max;
    float BMS_M22_Temp_min;
    float BMS_M23_Temp_max;
} BMSValues14_t;

// Bucket: BMS Values 15
// CAN ID: 0x1000003F
typedef struct
{
    float BMS_M23_Temp_min;
    float BMS_M24_Temp_max;
    float BMS_M24_Temp_min;
} BMSValues15_t;

// Bucket: BMS Values 6
// CAN ID: 0x10000036
typedef struct
{
    float BMS_M1_Temp_max;
    float BMS_M1_Temp_min;
    float BMS_M2_Temp_max;
    float BMS_M2_Temp_min;
    float BMS_M3_Temp_max;
} BMSValues6_t;

// Bucket: BMS Values 7
// CAN ID: 0x10000037
typedef struct
{
    float BMS_M3_Temp_min;
    float BMS_M4_Temp_max;
    float BMS_M4_Temp_min;
    float BMS_M5_Temp_max;
    float BMS_M5_Temp_min;
} BMSValues7_t;

// Bucket: BMS Values 8
// CAN ID: 0x10000038
typedef struct
{
    float BMS_M6_Temp_max;
    float BMS_M6_Temp_min;
    float BMS_M7_Temp_max;
    float BMS_M7_Temp_min;
    float BMS_M8_Temp_max;
} BMSValues8_t;

// Bucket: BMS Values 9
// CAN ID: 0x10000039
typedef struct
{
    float BMS_M8_Temp_min;
    float BMS_M9_Temp_max;
    float BMS_M9_Temp_min;
    float BMS_M10_Temp_max;
    float BMS_M10_Temp_min;
} BMSValues9_t;

// Bucket: Electrical System - Power & Energy2
// CAN ID: 0x10000022, 0x10000024, 0x10000025, 0x10000026, 0x10000027, 0x10000028
typedef struct
{
    float LV_Current_Act;
    float LV_Power_Act;
    uint32_t FuseBox1_State_Relay_9_14;
    uint32_t FuseBox1_Fuse_State_1_7;
    uint32_t FuseBox1_Fuse_State_8_14;
    uint32_t FuseBox1_Fuse_State_15_21;
    uint32_t FuseBox1_Fuse_State_22_28;
} ElectricalSystemPowerEnergy2_t;

// Bucket: FuseBox2
// CAN ID: 0x10000029, 0x1000002A, 0x1000002B, 0x1000002C, 0x1000002D, 0x1000002E, 0x10000035
typedef struct
{
    uint32_t FuseBox2_State_Relay_1_8;
    uint32_t FuseBox2_State_Relay_9_14;
    uint32_t FuseBox2_Fuse_State_1_7;
    uint32_t FuseBox2_Fuse_State_8_14;
    uint32_t FuseBox2_Fuse_State_15_21;
    uint32_t FuseBox2_Fuse_State_22_28;
    float BMS_PDU_Temp;
    float BMS_TargetTemp;
    uint32_t BMS_ThermalStatus;
} FuseBox2_t;

// Bucket: GearBox Temperatures 1
// CAN ID: 0x10000041
typedef struct
{
    float Temp_Gearbox_FL_IN;
    float Temp_Gearbox_FL_OUT;
    float Temp_Gearbox_FR_IN;
    float Temp_Gearbox_FR_OUT;
    float Temp_Gearbox_R_IN;
} GearBoxTemperatures1_t;

// Bucket: GearBox Temperatures 2
// CAN ID: 0x10000042
typedef struct
{
    float Temp_Gearbox_R_OUT;
} GearBoxTemperatures2_t;

// Bucket: Lighting Systems TX
// CAN ID: 0x00001002, 0x10000001
typedef struct
{
    uint32_t LowBeam_Req;
    uint32_t HighBeam_Req;
    uint32_t PosLight_Req;
    uint32_t IntLight_Req;
} LightingSystemsTX_t;

// Bucket: Pressure & Hydraulic Systems
// CAN ID: 0x10000010
typedef struct
{
    float Pres_Susp_Front;
    float Pres_Susp_Rear;
    float Pres_Brk_Front;
    float Pres_Brk_Rear;
} PressureHydraulicSystems_t;

// Bucket: Thermal Management
// CAN ID: 0x1000000C
typedef struct
{
    float BMS_Pack_Temp_max;
    float BMS_Pack_Temp_min;
    float Temp_Inv_FL;
    float Temp_Inv_FR;
    float Temp_Inv_RM;
} ThermalManagement_t;

// Bucket: Thermal Management2
// CAN ID: 0x1000000D
typedef struct
{
    float Temp_EM_FL;
    float Temp_EM_FR;
    float Temp_EM_RM;
    float Temp_DCDC;
    float Temp_ClntPump;
} ThermalManagement2_t;

// Bucket: Thermal Management3
// CAN ID: 0x1000000E
typedef struct
{
    float Temp_Battery;
    float Temp_Auxilaries;
    float Temp_AIR;
    float Temp_Powertrain;
} ThermalManagement3_t;


#ifdef __cplusplus
}
#endif

#endif
