#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
    CAN_Raw_Msg_t rawMsg;

    uint32_t processed = 10; // to avoid a storm of messages, process in frames

    while(processed > 0 &&
        osMessageQueueGet(guiMQHandle, &rawMsg, 0, 0) == osOK) {
        switch(rawMsg.id) {
            case CAN_ID_DRIVER_INPUT_AND_VEHICLE_CONTROL:
                if(parseDriverInput1(rawMsg, &divc)) // change only if required
                    modelListener->updateDriverControls(divc);
                break;
            case CAN_ID_DRIVER_INPUT_AND_VEHICLE_CONTROL2:
                if(parseDriverInput2(rawMsg, &divc2))
                    modelListener->updateSteering(divc2);
                break;
            case CAN_ID_POWERTRAIN_STATUS_AND_READINESS:
                if(parsePtStatus(rawMsg, &ptsr))
                    modelListener->updatePowertrainStatus(ptsr);
                break;
            case CAN_ID_MOTOR_AND_TORQUE_CONTROL1:
                if(parsemtc1(rawMsg, &mtc1))
                    modelListener->updateMotorTorque1(mtc1);
                break;
            case CAN_ID_MOTOR_AND_TORQUE_CONTROL2:
                if(parsemtc2(rawMsg, &mtc2))
                    modelListener->updateMotorTorque2(mtc2);
                break;
            case CAN_ID_EFFICIENCY_AND_PERFORMANCE:
                if(parseEffPerf(rawMsg, &ep))
                    modelListener->updateEfficiency(ep);
                break;
            case CAN_ID_PRESS_HYDRAULIC_LIGHT_POWERTRAIN:
                if(parsePressHydLightPt(rawMsg, &phlp))
                    modelListener->updatePressHydLightPt(phlp);
            break;
            case CAN_ID_AUXILIARY_STATES_LV_SOC:
                if(parseAuxStates(rawMsg, &aux))
                    modelListener->updateAux(aux);
                break;
            case CAN_ID_VEHICLE_STATE_1:
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

    rawVal = UnpackSignal(rawMsg.data, 48, 2);
    if(_vs1->RefSpdSend_Direction != (uint8_t)rawVal) {
        _vs1->RefSpdSend_Direction = (uint8_t)rawVal;
        changed = true;
    }

    return changed;
}

bool Model::parsePressHydLightPt(CAN_Raw_Msg_t rawMsg, Press_Hydraulic_Light_PowerTrain_t *_phlp) {
	uint64_t rawVal;
    bool changed = false;
    float rawFloat;

	rawVal = UnpackSignal(rawMsg.data, 0, 5);
	if(_phlp->Pres_Susp_Front != rawVal) {
		_phlp->Pres_Susp_Front = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 5, 5);
	if(_phlp->Pres_Susp_Rear != rawVal) {
		_phlp->Pres_Susp_Rear = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 10, 5);
	if(_phlp->Pres_Brk_Front != rawVal) {
		_phlp->Pres_Brk_Front = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 15, 5);
	if(_phlp->Pres_Brk_Rear != rawVal) {
		_phlp->Pres_Brk_Rear = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 20, 1);
	if(_phlp->LowBeam_St != rawVal) {
		_phlp->LowBeam_St = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 21, 1);
	if(_phlp->HighBeam_St != rawVal) {
		_phlp->HighBeam_St = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 22, 1);
	if(_phlp->PosLight_St != rawVal) {
		_phlp->PosLight_St = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 23, 1);
	if(_phlp->IntLight_St != rawVal) {
		_phlp->IntLight_St = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 24, 12);
	rawVal = rawVal -2500;
	if(_phlp->Pwr_Act_MotRM != rawVal) {
		_phlp->Pwr_Act_MotRM = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 36, 12);
	rawVal = rawVal -2500;
	if(_phlp->Pwr_Act_MotFL != rawVal) {
		_phlp->Pwr_Act_MotFL = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 48, 12);
	rawVal = rawVal -2500;
	if(_phlp->Pwr_Act_MotFR != rawVal) {
		_phlp->Pwr_Act_MotFR = rawVal;
		changed = true;
	}

	return changed;
}

bool Model::parsemtc1(CAN_Raw_Msg_t rawMsg, Motor_And_Torque_Control_1_t *_mtc) {
	int64_t rawVal;
    bool changed = false;
    float rawFloat;

	rawVal = UnpackSignal(rawMsg.data, 0, 16);
	rawVal = rawVal - 5000;
	if(_mtc->Trq_Act_Wheel_FL != rawVal) {
		_mtc->Trq_Req_Wheel_FL = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 16, 16);
	rawVal = rawVal - 5000;
	if(_mtc->Trq_Req_Wheel_FL != rawVal) {
		_mtc->Trq_Req_Wheel_FL = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 32, 16);
	rawVal = rawVal - 5000;
	if(_mtc->Trq_Act_Wheel_FR != rawVal) {
		_mtc->Trq_Act_Wheel_FR = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 48, 16);
	rawVal = rawVal - 5000;
	if(_mtc->Trq_Req_Wheel_FR != rawVal) {
		_mtc->Trq_Req_Wheel_FR = rawVal;
		changed = true;
	}

	return changed;
}

bool Model::parsemtc2(CAN_Raw_Msg_t rawMsg, Motor_And_Torque_Control_2_t *_mtc) {
	int64_t rawVal;
    bool changed = false;
    float rawFloat;

	rawVal = UnpackSignal(rawMsg.data, 0, 16);
	rawVal = rawVal - 5000;
	if(_mtc->Trq_Act_Wheel_RM != rawVal) {
		_mtc->Trq_Act_Wheel_RM = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 16, 16);
	rawVal = rawVal - 5000;
	if(_mtc->Trq_Req_Wheel_RM != rawVal) {
		_mtc->Trq_Req_Wheel_RM = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 32, 16);
	rawVal = rawVal - 2500;
	if(_mtc->Pwr_Disp != rawVal) {
		_mtc->Pwr_Disp = rawVal;
		changed = true;
	}

	rawVal = UnpackSignal(rawMsg.data, 48, 16);
	rawVal = rawVal - 5000;
	if(_mtc->Trq_Act_Sys != rawVal) {
		_mtc->Trq_Act_Sys = rawVal;
		changed = true;
	}

	return changed;
}

bool Model::parseEffPerf(CAN_Raw_Msg_t rawMsg, Efficiency_Performance_1_t *_ep) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    // Sys_Eff_Act (Start: 0, Len: 16)
    rawVal = UnpackSignal(rawMsg.data, 0, 8);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->Sys_Eff_Act - rawFloat) > 0.01f) {
        _ep->Sys_Eff_Act = rawFloat;
        changed = true;
    }

    // Sys_Eff_Opt (Start: 16, Len: 16)
    rawVal = UnpackSignal(rawMsg.data, 8, 8);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->Sys_Eff_Opt - rawFloat) > 0.01f) {
        _ep->Sys_Eff_Opt = rawFloat;
        changed = true;
    }
    
    // LongAccel (Start: 32, Len: 10)
    rawVal = UnpackSignal(rawMsg.data, 16, 10);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->LongAccel - rawFloat) > 0.01f) {
        _ep->LongAccel = rawFloat;
        changed = true;
    }
    
    // LatAccel (Start: 48, Len: 10)
    rawVal = UnpackSignal(rawMsg.data, 26, 10);
    rawFloat = (float)rawVal * 0.01f;
    if(fabs(_ep->LatAccel - rawFloat) > 0.01f) {
        _ep->LatAccel = rawFloat;
        changed = true;
    }

    rawVal = UnpackSignal(rawMsg.data, 36, 10);
    if(_ep->Rng_Rem != rawFloat) {
        _ep->Rng_Rem = rawFloat;
        changed = true;
    }

    rawVal = UnpackSignal(rawMsg.data, 46, 10);
    if(_ep->Rng_Added != rawFloat) {
        _ep->Rng_Added = rawFloat;
        changed = true;
    }
    
    return changed;
}

bool Model::parseAuxStates(CAN_Raw_Msg_t rawMsg, Auxiliary_States_LV_SOC_t *_aux) {
    uint64_t rawVal;
    bool changed = false;
    float rawFloat;

    rawVal = UnpackSignal(rawMsg.data, 0, 3);
	if(_aux->DCDC_State != rawVal) {
		_aux->DCDC_State = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 3, 3);
	if(_aux->AirComp_State != rawVal) {
		_aux->DCDC_State = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 6, 3);
	if(_aux->Heater_State != rawVal) {
		_aux->Heater_State = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 9, 3);
	if(_aux->HeatPump_State != rawVal) {
		_aux->HeatPump_State = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 9, 3);
	if(_aux->SteerByWire_State != rawVal) {
		_aux->SteerByWire_State = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 12, 10);
    rawVal = rawVal - 20;
	if(_aux->DCDC_HV_Current != rawVal) {
		_aux->DCDC_HV_Current = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 26, 10);
    rawVal = rawVal - 20;
	if(_aux->DCDC_HV_Voltage != rawVal) {
		_aux->DCDC_HV_Voltage = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 40, 8);
	if(_aux->SOC_Batt_HV != rawVal) {
		_aux->SOC_Batt_HV = rawVal;
		changed = true;
	}

    rawVal = UnpackSignal(rawMsg.data, 48, 8);
	if(_aux->LV_Voltage != rawVal) {
		_aux->LV_Voltage = rawVal;
		changed = true;
	}

    return changed;
}