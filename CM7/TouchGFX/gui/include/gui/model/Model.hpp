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
    DriverInputAndVehicleControl_t parseDriverInput1(CAN_Raw_Msg_t);
    PowertrainStatusAndReadiness_t parsePtStatus(CAN_Raw_Msg_t);
    DriverInputAndVehicleControl2_t parseDriverInput2(CAN_Raw_Msg_t);
    VehicleState1_t parseVehicleState(CAN_Raw_Msg_t);
};

#endif // MODEL_HPP
