#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "fdcan.h"

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual void updateDriverControls(DriverInputAndVehicleControl_t data) ;
	virtual void updateSteering(DriverInputAndVehicleControl2_t data) ;
	virtual void updatePowertrainStatus(PowertrainStatusAndReadiness_t data) ;
	virtual void updateHVSystem(ElectricalSystemPowerAndEnergy_t data) ;
	virtual void updateLVSystem(ElectricalSystemLVAndSOC2_t data) ;
	virtual void updateMotorTorque1(MotorAndTorqueControl1_t data) ;
	virtual void updateMotorTorque2(MotorAndTorqueControl2_t data) ;
	virtual void updateMotorTorque3(MotorAndTorqueControl3_t data) ;
	virtual void updateMotorTorque4(MotorAndTorqueControl4_t data) ;
	virtual void updateEfficiency(EfficiencyAndPerformance_t data) ;
	virtual void updateRange(EfficiencyAndPerformance2_t data) ;
	virtual void updateFaults(Faults_t data) ;
	virtual void updateWarnings(Warnings_t data) ;
	virtual void updatePowertrain(Powertrain_t data) ;
	virtual void updateGearbox(GearBoxAndParkBrake_t data) ;
	virtual void updateVehicleState(VehicleState1_t data) ;

    virtual ~Screen1Presenter() {}

private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
