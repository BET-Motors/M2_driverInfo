#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <gui/common/DataTypes.hpp>
#include <images/BitmapDatabase.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    void showDriverControls(DriverInputAndVehicleControl_t data);
	void showSteering(DriverInputAndVehicleControl2_t data);
	void showPowertrainStatus(PowertrainStatusAndReadiness_t data);	
	void showMotorTorque1(Motor_And_Torque_Control_1_t data);
	void showMotorTorque2(Motor_And_Torque_Control_2_t data);
	void showEfficiency(Efficiency_Performance_1_t data) ;
	void showPressHydLightPt(Press_Hydraulic_Light_PowerTrain_t data) ;
	void showAux(Auxiliary_States_LV_SOC_t data) ;
	void showVehicleState(VehicleState1_t data) ;
protected:
    long tickCounter = 0;       // To drive time-based animations
    float currentSpeed = 0.0f;  // Float for smooth acceleration
    float currentSteering = 0.0f;
    float currentSoc = 78.5f;   // Start battery at 78.5%
	bool canLeftActive = false; // State from CAN
	bool canRightActive = false;
	bool milActive = false;
};

#endif // SCREEN1VIEW_HPP
