#ifndef __BETDBCS3_H__
#define __BETDBCS3_H__

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
#define CAN_ID_BMS_CHARGING_CONTROL_TX              0x00001005
#define CAN_ID_BMS_CHARGING_CONTROL_RX_1            0x10000032
#define CAN_ID_BMS_CHARGING_CONTROL_RX_2            0x10000033
#define CAN_ID_BMS_VALUES_4                         0x10000034
#define CAN_ID_BMS_VALUES_5                         0x10000035

/*
 * CAN Signal Buckets
 * Generated from bucketList_screens3.csv
 * Standardized using typedefs.
 */

// Bucket: BMS & Charging Control TX
// CAN IDs: 0x00001005, 0x10000032, 0x10000033
typedef struct
{
    uint32_t Chrg_STOP_Req;
    uint32_t Chrg_PreCond_Req;
} BMSChargingControlTx_t;

typedef struct
{
    float BMS_Total_Dsg_Ah;
    float BMS_Total_Chg_Ah;
} BMSChargingControlRx1_t;

typedef struct
{
    float Charge_Time_Rem;
    uint32_t E_Lock_Status;
} BMSChargingControlRx2_t;

// Bucket: BMS Values 4
// CAN ID: 0x10000034
typedef struct
{
    float BMS_Max_Chg_CurrentLimit;
    float BMS_Max_Chg_VoltageLimit;
    float Charge_Pwr_Lim;
    uint32_t BMS_External_ChargeInfo;
    uint32_t BMS_Chg_ContFB;
} BMSValues4_t;

// Bucket: BMS Values 5
// CAN ID: 0x10000035
typedef struct
{
    float Temp_CCS2Charge_Inlet;
} BMSValues5_t;


#ifdef __cplusplus
}
#endif

#endif
