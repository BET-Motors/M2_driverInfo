#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "fdcan.h"

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
    CAN_GetDriverInputAndVehicleControl(&divc);
    CAN_GetDriverInputAndVehicleControl2(&divc2);
    CAN_GetPowertrainStatusAndReadiness(&ptsr);
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

	modelListener->updateDriverControls(divc);
	modelListener->updateSteering(divc2);       // Contains Rack Position
	modelListener->updatePowertrainStatus(ptsr);
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
}
