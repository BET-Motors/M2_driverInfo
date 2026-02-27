#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "fdcan.h"

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

	virtual void updateDriverControls(DriverInputAndVehicleControl_t data) {}
	virtual void updateSteering(DriverInputAndVehicleControl2_t data) {}
	virtual void updatePowertrainStatus(PowertrainStatusAndReadiness_t data) {}	
	virtual void updateMotorTorque1(Motor_And_Torque_Control_1_t data) {}
	virtual void updateMotorTorque2(Motor_And_Torque_Control_2_t data) {}
	virtual void updateEfficiency(Efficiency_Performance_1_t data) {}
	virtual void updatePressHydLightPt(Press_Hydraulic_Light_PowerTrain_t data) {}
	virtual void updateAux(Auxiliary_States_LV_SOC_t data) {}
	virtual void updateVehicleState(VehicleState1_t data) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
