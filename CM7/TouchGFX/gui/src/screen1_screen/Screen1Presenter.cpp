#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

// --- Driver Inputs ---

void Screen1Presenter::updateDriverControls(DriverInputAndVehicleControl_t data)
{
    view.showBrakeAccelposition(data.Acc_Ped_Pos, data.Brk_Ped_Pos);
    view.showGearSelect(data.PRND_State);
    view.updateDriveMode(data.Drv_Program);
    view.updateSteeringAndWheelAngle(data.StWhl_Angl_Act, data.Whl_Angl_Act);
}

void Screen1Presenter::updateSteering(DriverInputAndVehicleControl2_t data)
{
    view.setSteeringAngle(data.Sbw_Rack_Pos_Act);
}

// --- Powertrain Status ---

void Screen1Presenter::updatePowertrainStatus(PowertrainStatusAndReadiness_t data)
{
    view.updatePowertrainStatus(data.PT_Ready);
    view.updateDrivetrainStatus(data.DrvTrain_Status);
    view.updateMilStatus(data.MIL_Lamp_Status);
    view.udpateIndicators(data.Turn_Indicator_State);
}

// --- Electrical System ---

void Screen1Presenter::updateHVSystem(ElectricalSystemPowerAndEnergy_t data)
{
    view.updateLvHvVoltage(0, data.HV_Voltage);
}

void Screen1Presenter::updateLVSystem(ElectricalSystemLVAndSOC2_t data)
{
    view.updateLvHvVoltage(data.LV_Voltage, 0);
    view.updateBatteryState(data.SOC_Batt_HV);
}

// --- Motors & Torque ---

void Screen1Presenter::updateMotorTorque1(MotorAndTorqueControl1_t data)
{
}

void Screen1Presenter::updateMotorTorque2(MotorAndTorqueControl2_t data)
{
    // view.updateTorqueFR(data.Trq_Act_Wheel_FR);
}

void Screen1Presenter::updateMotorTorque3(MotorAndTorqueControl3_t data)
{
    // view.updateTorqueRM(data.Trq_Act_Wheel_RM);
}

void Screen1Presenter::updateMotorTorque4(MotorAndTorqueControl4_t data)
{
    // view.updateSystemTorque(data.Trq_Act_Sys);
}

// --- Performance & Efficiency ---

void Screen1Presenter::updateEfficiency(EfficiencyAndPerformance_t data)
{
    // view.updateGForce(data.LatAccel, data.LongAccel);
}

void Screen1Presenter::updateRange(EfficiencyAndPerformance2_t data)
{
    // view.updateRangeEstimates(data.Rng_Rem);
}

// --- Diagnostics ---

void Screen1Presenter::updateFaults(Faults_t data)
{
    // if (data.VCU_GeneralFaults_1 > 0) view.showCriticalFault();
}

void Screen1Presenter::updateWarnings(Warnings_t data)
{
    // view.updateWarningFlags(data.VCU_GeneralWarnings_1);
}

// --- Mechanical ---

void Screen1Presenter::updatePowertrain(Powertrain_t data)
{
    // view.updateMotorPower(data.Pwr_Act_MotFL, data.Pwr_Act_MotFR);
}

void Screen1Presenter::updateGearbox(GearBoxAndParkBrake_t data)
{
    // view.setParkBrakeIcon(data.ParkBrake_Status);
}

void Screen1Presenter::updateVehicleState(VehicleState1_t data)
{
    view.updateSpeedometer(data.Speed);
    // view.updateOdometer(data.Odometer);
}
