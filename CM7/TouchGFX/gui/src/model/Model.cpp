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

    // 2. Fetch the latest data (Thread-Safe)
    CAN_GetElectricalSystemPowerAndEnergy(&espe);
    CAN_GetElectricalSystemLvandsoc2(&esls2);
    CAN_GetMotorAndTorqueControl1(&mtc1);
    CAN_GetMotorAndTorqueControl2(&mtc2);
    CAN_GetMotorAndTorqueControl3(&mtc3);
    CAN_GetMotorAndTorqueControl4(&mtc4);
    CAN_GetEfficiencyAndPerformance(&ep);
    CAN_GetEfficiencyAndPerformance2(&ep2);
    CAN_GetFaults(&faults);
    CAN_GetWarnings(&warnings);
    CAN_GetPowertrain(&pt);
    CAN_GetGearboxAndParkbrake(&gbpb);
    CAN_GetVehicleState1(&vs1);

	modelListener->updateHVSystem(espe);        // HV Volt/Curr/Power
	modelListener->updateLVSystem(esls2);       // LV Volt/SOC

	// Torques
	modelListener->updateMotorTorque1(mtc1);
	modelListener->updateMotorTorque2(mtc2);
	modelListener->updateMotorTorque3(mtc3);
	modelListener->updateMotorTorque4(mtc4);

	// Efficiency & Range
	modelListener->updateEfficiency(ep);
	modelListener->updateRange(ep2);            // Contains Range Rem/Added

	// Diagnostics
	modelListener->updateFaults(faults);
	modelListener->updateWarnings(warnings);

	// Mechanical
	modelListener->updatePowertrain(pt);
	modelListener->updateGearbox(gbpb);
	modelListener->updateVehicleState(vs1);     // Odometer & Speed

    CAN_Raw_Msg_t rawMsg;

    while(osMessageQueueGet(guiMQHandle, &rawMsg, 0, 0) == osOK) {
        switch(rawMsg.id) {
            case 0x10000001:
                divc = parseDriverInput1(rawMsg);
                modelListener->updateDriverControls(divc);
                break;
            case 0x10000002:
                divc2 = parseDriverInput2(rawMsg);
                modelListener->updateSteering(divc2);
                break;
            case 0x10000003:
                ptsr = parsePtStatus(rawMsg);
                modelListener->updatePowertrainStatus(ptsr);
                break;

            case 0x10000043:
                // Odometer (Start: 0, Len: 32)
                vs1 = parseVehicleState(rawMsg);
                modelListener->updateVehicleState(vs1);
                break;
        }
    }
}

DriverInputAndVehicleControl_t Model::parseDriverInput1(CAN_Raw_Msg_t rawMsg) {
    uint64_t rawVal;

    DriverInputAndVehicleControl_t _divc;
    // Acc_Ped_Pos (Start: 0, Len: 8)
    rawVal = UnpackSignal(rawMsg.data, 0, 8);
    _divc.Acc_Ped_Pos = (uint32_t)rawVal;

    // Brk_Ped_Pos (Start: 8, Len: 8)
    rawVal = UnpackSignal(rawMsg.data, 8, 8);
    _divc.Brk_Ped_Pos = (uint32_t)rawVal;

    // PRND_State (Start: 16, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 16, 3);
    _divc.PRND_State = (uint32_t)rawVal;

    // Drv_Program (Start: 22, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 22, 3);
    _divc.Drv_Program = (uint32_t)rawVal;

    rawVal = UnpackSignal(rawMsg.data, 32, 16);
    _divc.StWhl_Angl_Act = ((float)rawVal * 0.1f) - 900.00f;

    rawVal = UnpackSignal(rawMsg.data, 48, 16);
    _divc.Whl_Angl_Act = ((float)rawVal * 0.1f) - 900.00f;

    return _divc;
}

PowertrainStatusAndReadiness_t Model::parsePtStatus(CAN_Raw_Msg_t rawMsg) {
    uint64_t rawVal;
    PowertrainStatusAndReadiness_t _ptsr;
    // PT_Ready (Start: 0, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 0, 1);
    _ptsr.PT_Ready = (uint32_t)rawVal;

    // DrvTrain_Status (Start: 1, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 1, 3);
    _ptsr.DrvTrain_Status = (uint32_t)rawVal;

    // MIL_Lamp_Status (Start: 4, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 4, 1);
    _ptsr.MIL_Lamp_Status = (uint32_t)rawVal;

    // Turn_Indicator_State (Start: 5, Len: 3)
    rawVal = UnpackSignal(rawMsg.data, 5, 3);
    _ptsr.Turn_Indicator_State = (uint32_t)rawVal;

    // HVDisconnect_Press (Start: 10, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 10, 1);
    _ptsr.HVDisconnect_Press = (uint32_t)rawVal;

    // Emergency_Press (Start: 12, Len: 1)
    rawVal = UnpackSignal(rawMsg.data, 12, 1);
    _ptsr.Emergency_Press = (uint32_t)rawVal;

    return _ptsr;
}

DriverInputAndVehicleControl2_t Model::parseDriverInput2(CAN_Raw_Msg_t rawMsg) {
    uint64_t rawVal;

    DriverInputAndVehicleControl2_t _divc2;

    // Sbw_Rack_Pos_Req (Start: 0, Len: 32)
    rawVal = UnpackSignal(rawMsg.data, 0, 32);
    _divc2.Sbw_Rack_Pos_Req = ((float)rawVal * 0.01f) - 500.00f;

    // Sbw_Rack_Pos_Act (Start: 32, Len: 32)
    rawVal = UnpackSignal(rawMsg.data, 32, 32);
    _divc2.Sbw_Rack_Pos_Act = ((float)rawVal * 0.01f) - 500.00f;
    return _divc2;
}

VehicleState1_t Model::parseVehicleState(CAN_Raw_Msg_t rawMsg) {
    uint64_t rawVal;
    VehicleState1_t _vs1;

    rawVal = UnpackSignal(rawMsg.data, 0, 32);
    _vs1.Odometer = (uint32_t)rawVal;

    // Speed (Start: 32, Len: 12)
    rawVal = UnpackSignal(rawMsg.data, 32, 12);
    _vs1.Speed = (float)rawVal * 0.1f;

    return _vs1;
}