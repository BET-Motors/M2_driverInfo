#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
    // 1. Declare local structs to hold the thread-safe copies
    DriverInputAndVehicleControl_t divc;
    DriverInputAndVehicleControl2_t divc2;
    PowertrainStatusAndReadiness_t ptsr;
    ElectricalSystemPowerAndEnergy_t espe;
    ElectricalSystemLVAndSOC2_t esls2;
    MotorAndTorqueControl1_t mtc1;
    MotorAndTorqueControl2_t mtc2;
    MotorAndTorqueControl3_t mtc3;
    MotorAndTorqueControl4_t mtc4;
    EfficiencyAndPerformance_t ep;
    EfficiencyAndPerformance2_t ep2;
    Faults_t faults;
    Warnings_t warnings;
    Powertrain_t pt;
    GearBoxAndParkBrake_t gbpb;
    VehicleState1_t vs1;

    CAN_Raw_Msg_t rawMsg;

    uint32_t processed = 10; // to avoid a storm of messages, process in frames

    while(processed > 0 &&
        osMessageQueueGet(guiMQHandle, &rawMsg, 0, 0) == osOK) {
        switch(rawMsg.id) {
            case 0x10000001:
                if(parseDriverInput1(rawMsg, &divc)) // change only if required
                    modelListener->updateDriverControls(divc);
                break;
            case 0x10000002:
                if(parseDriverInput2(rawMsg, &divc2))
                    modelListener->updateSteering(divc2);
                break;
            case 0x10000003:
                if(parsePtStatus(rawMsg, &ptsr))
                    modelListener->updatePowertrainStatus(ptsr);
                break;
            case 0x10000004:
                if(parseHVSystem(rawMsg, &espe))
                    modelListener->updateHVSystem(espe);
                break;
            case 0x10000005:
                if(parseLVSystem(rawMsg, &esls2))
                    modelListener->updateLVSystem(esls2);
                break;
            case 0x10000006:
                if(parseMtc1(rawMsg, &mtc1))
                    modelListener->updateMotorTorque1(mtc1);
                break;
            case 0x10000007:
                if(parseMtc2(rawMsg, &mtc2))
                    modelListener->updateMotorTorque2(mtc2);
                break;
            case 0x10000008:
                if(parseMtc3(rawMsg, &mtc3))
                    modelListener->updateMotorTorque3(mtc3);
                break;
            case 0x10000009:
                if(parseMtc4(rawMsg, &mtc4))
                    modelListener->updateMotorTorque4(mtc4);
                break;
            case 0x1000000A:
                if(parseEffPerf(rawMsg, &ep))
                    modelListener->updateEfficiency(ep);
                break;
            case 0x1000000B:
                if(parseEffPerf2(rawMsg, &ep2))
                    modelListener->updateRange(ep2);
            break;
            case 0x10000011:
                /* if(parseVcuGeneralFaults(rawMsg, &faults))
                    modelListener->updateFaults(faults); */
                break;
            case 0x10000012:
                // VCU_GeneralFaults_2 (Start: 0, Len: 64)
                /* rawVal = UnpackSignal(data, 0, 64);
                state.faults.VCU_GeneralFaults_2 = (uint64_t)rawVal; */
                break;
/* TODO: ADD THE FAULTS AND WARNINGS ACCORDING TO THE SCREEN */
            case 0x10000021:
                if(parsePowertrain(rawMsg, &pt))
                    modelListener->updatePowertrain(pt);
                break;
            case 0x10000040:
                if(parseGearbox(rawMsg, &gbpb))
                    modelListener->updateGearbox(gbpb);
                break;
            case 0x10000043:
                // Odometer (Start: 0, Len: 32)
                if(parseVehicleState(rawMsg, &vs1))
                    modelListener->updateVehicleState(vs1);
                break;
            default:
                break;
        }
        processed--;
    }
}

bool Model::parseDriverInput1(CAN_Raw_Msg_t rawMsg, DriverInputAndVehicleControl_t *_divc) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Acc_Ped_Pos (Start: 0, Len: 8)
    rawVal = UnpackSignal(rawMsg.data, 0, 8);
    if(_divc->Acc_Ped_Pos != (uint32_t)rawVal) {
        _divc->Acc_Ped_Pos = (uint32_t)rawVal;
        changed = true;
    }

    // Brk_Ped_Pos (Start: 8, Len: 8)
    rawVal = UnpackSignal(rawMsg.data, 8, 8);
    if(_divc->Brk_Ped_Pos != (uint32_t)rawVal) {
        _divc->Brk_Ped_Pos = (uint32_t)rawVal;
        changed = true;
    }

    // PRND_State (Start: 16, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 16, 3);
    if(_divc->PRND_State != (uint32_t)rawVal) {
        _divc->PRND_State = (uint32_t)rawVal;
        changed = true;
    }
    

    // Drv_Program (Start: 22, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 22, 3);
    if(_divc->Drv_Program != (uint32_t)rawVal) {
        _divc->Drv_Program = (uint32_t)rawVal;
        changed = true;
    }

    rawVal = UnpackSignal(rawMsg.data, 32, 16);
    rawFloat = ((float)rawVal * 0.1f) - 900.00f;
    if(fabs(_divc->StWhl_Angl_Act - rawFloat) > 0.1f) {
        _divc->StWhl_Angl_Act = rawFloat;
        changed = true;
    }

    rawVal = UnpackSignal(rawMsg.data, 48, 16);
    rawFloat = ((float)rawVal * 0.1f) - 900.00f;
    if(fabs(_divc->Whl_Angl_Act - rawFloat) > 0.1f) {
        _divc->Whl_Angl_Act = rawFloat;
        changed = true;
    }
    return changed;
}

bool Model::parsePtStatus(CAN_Raw_Msg_t rawMsg, PowertrainStatusAndReadiness_t *_ptsr) {
    uint64_t rawVal;
    bool changed = false;
    // PT_Ready (Start: 0, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 0, 1);
    if(_ptsr->PT_Ready != (uint32_t)rawVal) {
        _ptsr->PT_Ready = (uint32_t)rawVal;
        changed = true;
    }

    // DrvTrain_Status (Start: 1, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 1, 3);
    if(_ptsr->DrvTrain_Status != (uint32_t)rawVal) {
        _ptsr->DrvTrain_Status = (uint32_t)rawVal;
        changed = true;
    }

    // MIL_Lamp_Status (Start: 4, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 4, 1);
    if(_ptsr->MIL_Lamp_Status != (uint32_t)rawVal) {
        _ptsr->MIL_Lamp_Status = (uint32_t)rawVal;
        changed = true;
    }

    // Turn_Indicator_State (Start: 5, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 5, 3);
    if(_ptsr->Turn_Indicator_State != (uint32_t)rawVal) {
        _ptsr->Turn_Indicator_State = (uint32_t)rawVal;
        changed = true;
    }

    // HVDisconnect_Press (Start: 10, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 10, 1);
    if(_ptsr->HVDisconnect_Press != (uint32_t)rawVal) {
        _ptsr->HVDisconnect_Press = (uint32_t)rawVal;
        changed = true;
    }

    // Emergency_Press (Start: 12, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 12, 1);
    if(_ptsr->Emergency_Press != (uint32_t)rawVal) {
        _ptsr->Emergency_Press = (uint32_t)rawVal;
        changed = true;
    }

    return changed;
}

bool Model::parseDriverInput2(CAN_Raw_Msg_t rawMsg, DriverInputAndVehicleControl2_t *_divc2) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Sbw_Rack_Pos_Req (Start: 0, Len: 32)
    rawVal = UnpackSignal(rawMsg.data, 0, 32);
    rawFloat = ((float)rawVal * 0.01f) - 500.00f;
    if(fabs(_divc2->Sbw_Rack_Pos_Req - rawFloat) > 0.01f) {
        _divc2->Sbw_Rack_Pos_Req = rawFloat;
        changed = true;
    }

    // Sbw_Rack_Pos_Act (Start: 32, Len: 32)
    rawVal = UnpackSignal(rawMsg.data, 32, 32);
    rawFloat = ((float)rawVal * 0.01f) - 500.00f;
    if(fabs(_divc2->Sbw_Rack_Pos_Act - rawFloat) > 0.01f){
        _divc2->Sbw_Rack_Pos_Act = rawFloat;
        changed = true;
    }
    return changed;
}

bool Model::parseVehicleState(CAN_Raw_Msg_t rawMsg, VehicleState1_t *_vs1) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    rawVal = UnpackSignal(rawMsg.data, 0, 32);
    if(_vs1->Odometer != (uint32_t)rawVal) {
        _vs1->Odometer = (uint32_t)rawVal;
        changed = true;
    }

    // Speed (Start: 32, Len: 12)
    rawVal = UnpackSignal(rawMsg.data, 32, 12);
    rawFloat = (float)rawVal * 0.1f;
    if(fabs(_vs1->Speed - rawFloat) > 0.1f) {
        _vs1->Speed = (float)rawVal * 0.1f;
        changed = true;
    }

    return changed;
}

bool Model::parseHVSystem(CAN_Raw_Msg_t rawMsg, ElectricalSystemPowerAndEnergy_t *_espe) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    rawVal = UnpackSignal(rawMsg.data, 0, 16);
    rawFloat = (float)rawVal * 0.1f;
    if(fabs(_espe->HV_Voltage - rawFloat) > 0.1f) {
        _espe->HV_Voltage = rawFloat;
        changed = true;
    }

    // HV_Current (Start: 16, Len: 16)
    rawVal = UnpackSignal(rawMsg.data, 16, 16);
    rawFloat = ((float)rawVal * 0.1f) - 2500.00f;
    if(fabs(_espe->HV_Current - rawFloat) > 0.1f) {
        _espe->HV_Current = rawFloat;
        changed = true;
    }

    // HV_Power (Start: 32, Len: 32)
    rawVal = UnpackSignal(rawMsg.data, 32, 32);
    rawFloat = ((float)rawVal * 0.01f) - 2500.00f;
    if(fabs(_espe->HV_Power - rawFloat) > 0.1f) {
        _espe->HV_Power = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseLVSystem(CAN_Raw_Msg_t rawMsg, ElectricalSystemLVAndSOC2_t *_esls2) {
    uint64_t rawVal;
    float rawFloat;
    bool changed = false;

    // SOC_Batt_HV (Start: 0, Len: 8)
    rawVal = UnpackSignal(rawMsg.data, 0, 8);
    if(_esls2->SOC_Batt_HV != (uint32_t)rawVal) {
        _esls2->SOC_Batt_HV = (uint32_t)rawVal;
        changed = true;
    }

    // LV_Voltage (Start: 16, Len: 32)
    rawVal = UnpackSignal(rawMsg.data, 16, 32);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_esls2->LV_Voltage - rawFloat) > 0.01f) {
        _esls2->LV_Voltage = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseMtc1(CAN_Raw_Msg_t rawMsg, MotorAndTorqueControl1_t *_mtc1) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;
    
    // Trq_Act_Wheel_FL (Start: 0, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 0, 20);
    rawFloat = ((float)rawVal * 0.1f) - 5000.00f;
    if(fabs(_mtc1->Trq_Act_Wheel_FL - rawFloat) > 0.1f) {
        _mtc1->Trq_Act_Wheel_FL = rawFloat;
        changed = true;
    }

    // Trq_Req_Wheel_FL (Start: 32, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 32, 20);
    rawFloat = ((float)rawVal * 0.1f) - 5000.00f;
    if(fabs(_mtc1->Trq_Req_Wheel_FL - rawFloat) > 0.1f) {
        _mtc1->Trq_Req_Wheel_FL = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseMtc2(CAN_Raw_Msg_t rawMsg, MotorAndTorqueControl2_t *_mtc2) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;
    
    // Trq_Act_Wheel_FL (Start: 0, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 0, 20);
    rawFloat = ((float)rawVal * 0.1f) - 5000.00f;
    if(fabs(_mtc2->Trq_Act_Wheel_FR - rawFloat) > 0.1f) {
        _mtc2->Trq_Act_Wheel_FR = rawFloat;
        changed = true;
    }

    // Trq_Req_Wheel_FL (Start: 32, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 32, 20);
    rawFloat = ((float)rawVal * 0.1f) - 5000.00f;
    if(fabs(_mtc2->Trq_Req_Wheel_FR - rawFloat) > 0.1f) {
        _mtc2->Trq_Req_Wheel_FR = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseMtc3(CAN_Raw_Msg_t rawMsg, MotorAndTorqueControl3_t *_mtc3) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Trq_Act_Wheel_FL (Start: 0, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 0, 20);
    rawFloat = ((float)rawVal * 0.1f) - 5000.00f;
    if(fabs(_mtc3->Trq_Act_Wheel_RM - rawFloat) > 0.1f) {
        _mtc3->Trq_Act_Wheel_RM = rawFloat;
        changed = true;
    }

    // Trq_Req_Wheel_FL (Start: 32, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 32, 20);
    rawFloat = ((float)rawVal * 0.1f) - 5000.00f;
    if(fabs(_mtc3->Trq_Req_Wheel_RM - rawFloat) > 0.1f) {
        _mtc3->Trq_Req_Wheel_RM = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseMtc4(CAN_Raw_Msg_t rawMsg, MotorAndTorqueControl4_t *_mtc4) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Trq_Act_Wheel_FL (Start: 0, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 0, 20);
    rawFloat = ((float)rawVal * 0.1f) - 2500.00f;
    if(fabs(_mtc4->Pwr_Disp - rawFloat) > 0.1f) {
        _mtc4->Pwr_Disp = rawFloat;
        changed = true;
    }

    // Trq_Req_Wheel_FL (Start: 32, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 32, 20);
    rawFloat = ((float)rawVal * 0.1f) - 5000.00f;
    if(fabs(_mtc4->Trq_Act_Sys - rawFloat) > 0.1f) {
        _mtc4->Trq_Act_Sys = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseEffPerf(CAN_Raw_Msg_t rawMsg, EfficiencyAndPerformance_t *_ep) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Sys_Eff_Act (Start: 0, Len: 16)
    rawVal = UnpackSignal(rawMsg.data, 0, 16);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->Sys_Eff_Act - rawFloat) > 0.01f) {
        _ep->Sys_Eff_Act = rawFloat;
        changed = true;
    }

    // Sys_Eff_Opt (Start: 16, Len: 16)
    rawVal = UnpackSignal(rawMsg.data, 16, 16);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->Sys_Eff_Opt - rawFloat) > 0.01f) {
        _ep->Sys_Eff_Opt = rawFloat;
        changed = true;
    }
    
    // LongAccel (Start: 32, Len: 10)
    rawVal = UnpackSignal(rawMsg.data, 32, 10);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->LongAccel - rawFloat) > 0.01f) {
        _ep->LongAccel = rawFloat;
        changed = true;
    }
    
    // LatAccel (Start: 48, Len: 10)
    rawVal = UnpackSignal(rawMsg.data, 48, 10);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->LatAccel - rawFloat) > 0.01f) {
        _ep->LatAccel = rawFloat;
        changed = true;
    }
    
    return changed;
}

bool Model::parseEffPerf2(CAN_Raw_Msg_t rawMsg, EfficiencyAndPerformance2_t *_ep2) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Rng_Rem (Start: 0, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 0, 20);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep2->Rng_Rem - rawFloat) > 0.01f) {
        _ep2->Rng_Rem = rawFloat;
        changed = true;
    }

    // Rng_Added (Start: 32, Len: 20)
    rawVal = UnpackSignal(rawMsg.data, 32, 20);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep2->Rng_Added - rawFloat) > 0.01f) {
        _ep2->Rng_Added = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseFaults(CAN_Raw_Msg_t rawMsg, Faults_t *_faults) {
    uint64_t rawVal;
    bool changed = false;

    // VCU_GeneralFaults_1 (Start: 0, Len: 64)
    /* rawVal = UnpackSignal(rawMsg.data, 0, 64);
    if(_faults->VCU_GeneralFaults_1 != (uint64_t) rawVal) {
        _faults.VCU_GeneralFaults_1 = (uint64_t)rawVal;
        changed = true;
    } */

    return changed;
}

bool Model::parseWarnings(CAN_Raw_Msg_t rawMsg, Warnings_t *_warnings) {
    uint64_t rawVal;
    bool changed = false;

    // VCU_GeneralFaults_1 (Start: 0, Len: 64)
    /* rawVal = UnpackSignal(rawMsg.data, 0, 64);
    if(_warnings->VCU_GeneralWarnings_1 != (uint64_t) rawVal) {
        _warnings.VCU_GeneralWarnings_1 = (uint64_t) rawVal;
        changed = true;
    } */

    return changed;
}

bool Model::parsePowertrain(CAN_Raw_Msg_t rawMsg, Powertrain_t *_pt) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Pwr_Act_MotRM (Start: 0, Len: 16)    
    rawVal = UnpackSignal(rawMsg.data, 0, 16);
    rawFloat = ((float)rawVal * 0.1f) - 2500.00f;
    if(fabs(_pt->Pwr_Act_MotRM - rawFloat) > 0.1f) {
        _pt->Pwr_Act_MotRM = rawFloat;
        changed = true;
    }
    
    // Pwr_Act_MotFL (Start: 16, Len: 16)
    rawVal = UnpackSignal(rawMsg.data, 16, 16);
    rawFloat = ((float)rawVal * 0.1f) - 2500.00f;
    if(fabs(_pt->Pwr_Act_MotFL - rawFloat) > 0.1f) {
        _pt->Pwr_Act_MotFL = rawFloat;
        changed = true;
    }

    // Pwr_Act_MotFR (Start: 32, Len: 16)
    rawVal = UnpackSignal(rawMsg.data, 32, 16);
    rawFloat = ((float)rawVal * 0.1f) - 2500.00f;
    if(fabs(_pt->Pwr_Act_MotFR - rawFloat) > 0.1f) {
        _pt->Pwr_Act_MotFR = rawFloat;
        changed = true;
    }

    return changed;
}

bool Model::parseGearbox(CAN_Raw_Msg_t rawMsg, GearBoxAndParkBrake_t *_gbpb) {
    uint64_t rawVal;
    bool changed = false;

    // ParkBrake_Status (Start: 0, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 0, 3);
    if(_gbpb->ParkBrake_Status != (uint32_t)rawVal) {
        _gbpb->ParkBrake_Status = (uint32_t)rawVal;
        changed = true;
    }

    // GearShift_FL_Act_Pos (Start: 4, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 4, 3);
    if(_gbpb->GearShift_FL_Act_Pos != (uint32_t)rawVal) {
        _gbpb->GearShift_FL_Act_Pos = (uint32_t)rawVal;
        changed = true;
    }

    // GearShift_FR_Act_Pos (Start: 8, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 8, 3);
    if(_gbpb->GearShift_FR_Act_Pos != (uint32_t)rawVal) {
        _gbpb->GearShift_FR_Act_Pos = (uint32_t)rawVal;
        changed = true;
    }

    return changed;
}