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
    view.showDriverControls(data);
}

void Screen1Presenter::updateSteering(DriverInputAndVehicleControl2_t data)
{
    view.showSteering(data);
}

void Screen1Presenter::updatePowertrainStatus(PowertrainStatusAndReadiness_t data)
{
    view.showPowertrainStatus(data);
}

void Screen1Presenter::updateMotorTorque1(Motor_And_Torque_Control_1_t data) {
    view.showMotorTorque1(data);
}

void Screen1Presenter::updateMotorTorque2(Motor_And_Torque_Control_2_t data)
{
    view.showMotorTorque2(data);
}

void Screen1Presenter::updateEfficiency(Efficiency_Performance_1_t data)
{
    view.showEfficiency(data);
}

void Screen1Presenter::updatePressHydLightPt(Press_Hydraulic_Light_PowerTrain_t data) {
    view.showPressHydLightPt(data);
}

void Screen1Presenter::updateVehicleState(VehicleState1_t data)
{
    view.showVehicleState(data);
}


void Screen1Presenter::updateAux(Auxiliary_States_LV_SOC_t data) {
    view.showAux(data);
}