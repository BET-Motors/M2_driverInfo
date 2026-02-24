#ifndef MODEL_HPP
#define MODEL_HPP

#include "fdcan.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

protected:
    ModelListener* modelListener;

private:
    bool parseDriverInput1(CAN_Raw_Msg_t, DriverInputAndVehicleControl_t *);
    bool parsePtStatus(CAN_Raw_Msg_t, PowertrainStatusAndReadiness_t *);
    bool parseDriverInput2(CAN_Raw_Msg_t, DriverInputAndVehicleControl2_t *);
    bool parseVehicleState(CAN_Raw_Msg_t, VehicleState1_t *);
    bool parseHVSystem(CAN_Raw_Msg_t, ElectricalSystemPowerAndEnergy_t *);
    bool parseLVSystem(CAN_Raw_Msg_t, ElectricalSystemLVAndSOC2_t *);
    bool parseMtc1(CAN_Raw_Msg_t, MotorAndTorqueControl1_t *);
    bool parseMtc2(CAN_Raw_Msg_t, MotorAndTorqueControl2_t *);
    bool parseMtc3(CAN_Raw_Msg_t, MotorAndTorqueControl3_t *);
    bool parseMtc4(CAN_Raw_Msg_t, MotorAndTorqueControl4_t *);
    bool parseEffPerf(CAN_Raw_Msg_t, EfficiencyAndPerformance_t *);
    bool parseEffPerf2(CAN_Raw_Msg_t, EfficiencyAndPerformance2_t *);
    bool parseFaults(CAN_Raw_Msg_t, Faults_t *);
    bool parseWarnings(CAN_Raw_Msg_t, Warnings_t *);
    bool parsePowertrain(CAN_Raw_Msg_t, Powertrain_t *);
    bool parseGearbox(CAN_Raw_Msg_t, GearBoxAndParkBrake_t *);
};

#endif // MODEL_HPP
