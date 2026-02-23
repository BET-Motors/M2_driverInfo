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

    void handleTickEvent();
    void showBrakeAccelposition(uint8_t brakPercent, uint8_t accelPercent);
    void showGearSelect(uint8_t prndState);
    void updateSteeringAndWheelAngle(uint16_t steeringWhlAng, uint16_t wheelAngle);
    void updatePowertrainStatus(uint8_t status);
    void updateDrivetrainStatus(uint8_t status);
    void udpateIndicators(uint8_t status);
    void updateDriveMode(uint8_t status);
    void updateBatteryState(uint8_t soc);
    void updateMilStatus(uint8_t status);
    void updateLightingStatus(Lights_t status);
    void updateRangeRemaining(uint16_t range);
    void updateLvHvVoltage(uint16_t lv, uint16_t hv);
    void updateAccel(uint16_t latAccel, uint16_t longAccel);
    void updateSysEff(uint16_t actEff, uint16_t optEff);
    void updateFlTorqueAndPower(uint32_t flTrqAct, uint32_t flPwrAct);
    void updateFrTorqueAndPower(uint32_t frTrqAct, uint32_t frPwrAct);
    void updateRlRrTorqueAndPower(uint32_t RlTrqAct, uint32_t RrTrqAct, uint32_t RmPower);
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
