#ifndef MODEL_HPP
#define MODEL_HPP

#include "fdcan.h"

class ModelListener;

class Model
{
private:
    // 1. Declare local structs to hold the thread-safe copies
    DriverInputAndVehicleControl_t divc;
    DriverInputAndVehicleControl2_t divc2;
    PowertrainStatusAndReadiness_t ptsr;
    VehicleState1_t vs1;
    Press_Hydraulic_Light_PowerTrain_t phlp;
    Motor_And_Torque_Control_1_t mtc1;
    Motor_And_Torque_Control_2_t mtc2;
    Efficiency_Performance_1_t ep;
    Auxiliary_States_LV_SOC_t aux;

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
    bool parsePressHydLightPt(CAN_Raw_Msg_t, Press_Hydraulic_Light_PowerTrain_t *);
    bool parsemtc1(CAN_Raw_Msg_t, Motor_And_Torque_Control_1_t *);
    bool parsemtc2(CAN_Raw_Msg_t, Motor_And_Torque_Control_2_t *);
    bool parseEffPerf(CAN_Raw_Msg_t, Efficiency_Performance_1_t *);
    bool parseAuxStates(CAN_Raw_Msg_t, Auxiliary_States_LV_SOC_t *);
};

#endif // MODEL_HPP
