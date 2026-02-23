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
	virtual void updateHVSystem(ElectricalSystemPowerAndEnergy_t data) {}
	virtual void updateLVSystem(ElectricalSystemLVAndSOC2_t data) {}
	virtual void updateMotorTorque1(MotorAndTorqueControl1_t data) {}
	virtual void updateMotorTorque2(MotorAndTorqueControl2_t data) {}
	virtual void updateMotorTorque3(MotorAndTorqueControl3_t data) {}
	virtual void updateMotorTorque4(MotorAndTorqueControl4_t data) {}
	virtual void updateEfficiency(EfficiencyAndPerformance_t data) {}
	virtual void updateRange(EfficiencyAndPerformance2_t data) {}
	virtual void updateFaults(Faults_t data) {}
	virtual void updateWarnings(Warnings_t data) {}
	virtual void updatePowertrain(Powertrain_t data) {}
	virtual void updateGearbox(GearBoxAndParkBrake_t data) {}
	virtual void updateVehicleState(VehicleState1_t data) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
