#include <gui/screen1_screen/Screen1View.hpp>
#include <math.h> // Required for sinf(), cosf()
#include "fdcan.h"

Screen1View::Screen1View()
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
//    Unicode::snprintf(socBuffer, SOC_SIZE, "%d", 0);
//	soc.invalidate();
    Unicode::snprintf(textAreaPrndBuffer, TEXTAREAPRND_SIZE, "%c", 'P');
    textAreaPrnd.invalidate();
	Unicode::snprintf(rangeBuffer, RANGE_SIZE, "%d", 100);
	range.invalidate();
	Unicode::snprintf(odoBuffer, ODO_SIZE, "%d", 1231230);
	odo.invalidate();
	Unicode::snprintf(steeringAngleBuffer, STEERINGANGLE_SIZE, "%d", 180);
	steeringAngle.invalidate();
	Unicode::snprintf(socBuffer, SOC_SIZE, "%d", 000);
	soc.invalidate();
	Unicode::fromUTF8((const uint8_t*)"SPORT", driveModeBuffer, DRIVEMODE_SIZE);
	driveMode.invalidate();
	Unicode::snprintf(torquePower_FLBuffer1, TORQUEPOWER_FLBUFFER1_SIZE, "%d", 10000);
	Unicode::snprintf(torquePower_FLBuffer2, TORQUEPOWER_FLBUFFER2_SIZE, "%d", 10000);
	torquePower_FL.invalidate();
	Unicode::snprintf(torquePower_FRBuffer1, TORQUEPOWER_FRBUFFER1_SIZE, "%d", 10000);
	Unicode::snprintf(torquePower_FRBuffer2, TORQUEPOWER_FRBUFFER2_SIZE, "%d", 10000);
	torquePower_FR.invalidate();
	Unicode::snprintf(torquePower_RRBuffer, TORQUEPOWER_RR_SIZE, "%d", 10000);
	Unicode::snprintf(torquePower_RLBuffer, TORQUEPOWER_RL_SIZE, "%d", 10000);
	torquePower_RR.invalidate();
	torquePower_RL.invalidate();
	Unicode::snprintf(linearSpeedBuffer, LINEARSPEED_SIZE, "%d", 000);
	linearSpeed.invalidate();
	Unicode::snprintf(driveTrainStatusBuffer, DRIVETRAINSTATUS_SIZE, "%s", "IDLE");
	driveTrainStatus.invalidate();
	canLeftActive = false;
	canRightActive = false;
	milActive = false;
}

void Screen1View::showBrakeAccelposition(uint8_t brakePosition, uint8_t accelPosition) {
	accelPedal.setValue(accelPosition);
	brakePedal.setValue(brakePosition);
}

void Screen1View::updateMilStatus(uint8_t status) {
	if(status == 1) {
		milActive = true;
	} else {
		milActive = false;
	}
}

void Screen1View::updateLightingStatus(Lights_t status) {
	if(status.lowBeam) {
		headlight.setBitmap(BITMAP_LOWBEAM_ID);
	} else if(status.highBeam) {
		headlight.setBitmap(BITMAP_HIGHBEAM_ID);
	}

	if(status.posLights) {
		posLights.setBitmap(BITMAP_POSLIGHTSACTIVE_ID);
	} else if(!status.posLights) {
		posLights.setBitmap(BITMAP_POSLIGHTSINACTIVE_ID);
	}

	if(status.intLights) {
		intLight.setBitmap(BITMAP_INTLIGHTACTIVE_ID);
	} else if(!status.intLights) {
		intLight.setBitmap(BITMAP_INTLIGHTINACTIVE_ID);
	}

	if(!status.lowBeam && !status.highBeam) {
		headlight.setBitmap(BITMAP_HEADLIGHTSINACTIVE_ID);
	}
}

void Screen1View::updateRangeRemaining(uint16_t rangeVal) {
	Unicode::snprintf(rangeBuffer, RANGE_SIZE, "%d", rangeVal);
	range.invalidate();
}

void Screen1View::updateLvHvVoltage(uint16_t lvValue, uint16_t hvValue) {
	Unicode::snprintf(hvBuffer, HV_SIZE, "%d", hvValue);
	hv.invalidate();
	Unicode::snprintf(lvBuffer, LV_SIZE, "%d", lvValue);
	lv.invalidate();
}

void Screen1View::showGearSelect(uint8_t prndState)
{
	char gearString = '-'; // Default if signal is invalid

	switch (prndState)
	{
	case 0: // CAN says 0 is Neutral
		gearString = 'N';
		break;
	case 1: // CAN says 1 is Park
		gearString = 'P';
		break;
	case 2: // CAN says 2 is Drive
		gearString = 'D';
		break;
	case 3: // CAN says 3 is Reverse
		gearString = 'R';
		break;
	default:
		gearString = '-'; // Error or invalid state
		break;
	}
	Unicode::snprintf(textAreaPrndBuffer, TEXTAREAPRND_SIZE, "%c", gearString);
	textAreaPrnd.invalidate();
}

void Screen1View::updatePowertrainStatus(uint8_t status) {
	switch(status) {
		case 0:
			powertrainStatus.setBitmap(BITMAP_BATTERYNOTREADY_ID);
			break;
		case 1:
			powertrainStatus.setBitmap(BITMAP_BATTERYREADY_ID);
			break;
	}
}

void Screen1View::updateSteeringAndWheelAngle(uint16_t steeringWhlAng, uint16_t wheelAngle) {
	float steeringRad = steeringWhlAng * (3.14159f / 180.0f); // angles are in °
	float wheelRad = wheelAngle * (3.14159f / 180.0f);

	Unicode::snprintfFloat(steeringAngleBuffer, STEERINGANGLE_SIZE, "%.1f", steeringWhlAng);
	steeringAngle.invalidate();

	steeringWheel.updateZAngle(steeringRad);
	steeringWheel.invalidate();

	frontLeftWheel.updateZAngle(steeringRad);
	frontRightWheel.updateZAngle(steeringRad);

	// Invalidate tires to redraw
	frontLeftWheel.invalidate();
	frontRightWheel.invalidate();

	Unicode::snprintfFloat(wheelAngle_FLBuffer, WHEELANGLE_FL_SIZE, "%.1f", wheelAngle);
	wheelAngle_FL.invalidate();
	Unicode::snprintfFloat(wheelAngle_FRBuffer, WHEELANGLE_FR_SIZE, "%.1f", wheelAngle);
	wheelAngle_FR.invalidate();

	// TODO: THERE MUST BE SOME CORRELATION BETWEEN THE STEERING ANGLE AND THE WHEEL ANGLE
	// I.E. FOR 1° MOVEMENT OF THE STEERING WHEEL, HOW MUCH DOES THE STEERING WHEEL MOVES.
	// This will be required when we check if the steering wheel angle and the wheel
	// angle are correlated. For now, we simply check if they are equal.

//	if((int)steeringRad != (int)wheelRad) {
//		frontLeftWheel.cancelAnimationTextureMapperAnimation();
//		frontRightWheel.cancelAnimationTextureMapperAnimation();
//		frontLeftWheel.setBitmap(BITMAP_TYREINCORRECT_ID);
//		frontRightWheel.setBitmap(BITMAP_TYREINCORRECT_ID);
//		frontLeftWheel.invalidate();
//		frontRightWheel.invalidate();
//		frontLeftWheel.startAnimation();
//		frontRightWheel.startAnimation();
//	}
}

void Screen1View::updateAccel(uint16_t latAccel, uint16_t longAccel) {
	Unicode::snprintf(accelCharBuffer1, ACCELCHARBUFFER1_SIZE, "%d", latAccel);
	Unicode::snprintf(accelCharBuffer2, ACCELCHARBUFFER2_SIZE, "%d", longAccel);
	accelChar.invalidate();
}

void Screen1View::updateSysEff(uint16_t actEffVal, uint16_t optEffVal) {
	Unicode::snprintf(optEffBuffer, ACTEFF_SIZE, "%d", optEffVal);
	Unicode::snprintf(actEffBuffer, OPTEFF_SIZE, "%d", actEffVal);
	actEff.invalidate();
	optEff.invalidate();
}

void Screen1View::updateFlTorqueAndPower(uint32_t flTrqAct, uint32_t flPwrAct) {
	Unicode::snprintf(torquePower_FLBuffer1, TORQUEPOWER_FLBUFFER1_SIZE, "%d", flTrqAct);
	Unicode::snprintf(torquePower_FLBuffer2, TORQUEPOWER_FLBUFFER2_SIZE, "%d", flPwrAct);
	torquePower_FL.invalidate();
}

void Screen1View::updateFrTorqueAndPower(uint32_t frTrqAct, uint32_t frPwrAct) {
	Unicode::snprintf(torquePower_FRBuffer1, TORQUEPOWER_FRBUFFER1_SIZE, "%d", frTrqAct);
	Unicode::snprintf(torquePower_FRBuffer2, TORQUEPOWER_FRBUFFER2_SIZE, "%d", frPwrAct);
	torquePower_FR.invalidate();
}

void Screen1View::updateRlRrTorqueAndPower(uint32_t RlTrqAct, uint32_t RrTrqAct, uint32_t RmPower) {
	Unicode::snprintf(torquePower_RRBuffer, TORQUEPOWER_RR_SIZE, "%d", RlTrqAct);
	Unicode::snprintf(torquePower_RLBuffer, TORQUEPOWER_RL_SIZE, "%d", RrTrqAct);
	torquePower_RR.invalidate();
	torquePower_RL.invalidate();
	Unicode::snprintf(rmPowerBuffer, RMPOWER_SIZE, "%d", RmPower);
	rmPower.invalidate();
}

void Screen1View::udpateIndicators(uint8_t status) {
	switch(status) {
		case 0:
			canLeftActive = false;
			canRightActive = false;
			hazardLight.setBitmap(BITMAP_HAZARDLIGHTINACTIVE_ID);
			hazardLight.invalidate();
			break;
		case 1:
			canLeftActive = true;
			canRightActive = false;
			break;
		case 2:
			canLeftActive = false;
			canRightActive = true;
			break;
		case 3:
			canRightActive = true;
			canLeftActive = true;
			hazardLight.setBitmap(BITMAP_HAZARDLIGHTACTIVE_ID);
			hazardLight.invalidate();
			break;
		default:
			canLeftActive = false;
			canRightActive = false;
			hazardLight.setBitmap(BITMAP_HAZARDLIGHTINACTIVE_ID);
			hazardLight.invalidate();
			break;
	}
}

void Screen1View::updateDrivetrainStatus(uint8_t status) {
	switch(status) {
		case 0:
			Unicode::fromUTF8((const uint8_t*)"IDLE", driveTrainStatusBuffer, DRIVETRAINSTATUS_SIZE);
			driveTrainStatus.invalidate();
			break;
		case 1:
			Unicode::fromUTF8((const uint8_t*)"RWD", driveTrainStatusBuffer, DRIVETRAINSTATUS_SIZE);
			driveTrainStatus.invalidate();
			break;
		case 2:
			Unicode::fromUTF8((const uint8_t*)"AWD LOW", driveTrainStatusBuffer, DRIVETRAINSTATUS_SIZE);
			driveTrainStatus.invalidate();
			break;
		case 3:
			Unicode::fromUTF8((const uint8_t*)"AWD HIGH", driveTrainStatusBuffer, DRIVETRAINSTATUS_SIZE);
			driveTrainStatus.invalidate();
			break;
		default:
			Unicode::fromUTF8((const uint8_t*)"IDLE", driveTrainStatusBuffer, DRIVETRAINSTATUS_SIZE);
			driveTrainStatus.invalidate();
			break;
	}
}

void Screen1View::updateDriveMode(uint8_t status) {
	switch(status) {
		case 0:
			Unicode::fromUTF8((const uint8_t*)"ECO", driveModeBuffer, DRIVEMODE_SIZE);
			driveMode.invalidate();
			break;
		case 1:
			Unicode::fromUTF8((const uint8_t*)"SPORT", driveModeBuffer, DRIVEMODE_SIZE);
			driveMode.invalidate();
			break;
		case 2:
			Unicode::fromUTF8((const uint8_t*)"SNOW", driveModeBuffer, DRIVEMODE_SIZE);
			driveMode.invalidate();
			break;
	}
}

void Screen1View::updateBatteryState(uint8_t charge) {
	batteryState.setValue(charge); // assuming the charge is in %
	Unicode::snprintf(socBuffer, SOC_SIZE, "%d", charge);
	soc.invalidate();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

//void Screen1View::handleTickEvent()
//{
//    tickCounter++;
//
//    // ==========================================
//    // 1. STEERING SIMULATION (Sine Wave)
//    // ==========================================
//    // Oscillate between -60 and +60 degrees over time
//    // 0.03f controls the speed of the steering
//    float steeringDeg = 60.0f * sinf(tickCounter * 0.03f);
//
//
//    // Convert to Radians for TextureMapper (Rad = Deg * PI / 180)
//    float steeringRad = steeringDeg * (3.14159f / 180.0f);
//    Unicode::snprintfFloat(steeringAngleBuffer, STEERINGANGLE_SIZE, "%.1f", steeringDeg);
//	steeringAngle.invalidate();
//    Unicode::snprintfFloat(wheelAngle_FLBuffer, WHEELANGLE_FL_SIZE, "%.1f", steeringDeg);
//    wheelAngle_FL.invalidate();
//    Unicode::snprintfFloat(wheelAngle_FRBuffer, WHEELANGLE_FR_SIZE, "%.1f", steeringDeg);
//    wheelAngle_FR.invalidate();
//    // Apply to Steering Wheel
//    steeringWheel.updateZAngle(steeringRad);
//    steeringWheel.invalidate();
//
//    // Apply to Front Tires (Assuming you named them like this)
//    // Note: Tires might need an offset depending on your image orientation
//    frontLeftWheel.updateZAngle(steeringRad);
//    frontRightWheel.updateZAngle(steeringRad);
//
//    // Invalidate tires to redraw
//    frontLeftWheel.invalidate();
//    frontRightWheel.invalidate();
//
//
//    // ==========================================
//    // 2. SPEED & PEDAL PHYSICS
//    // ==========================================
//    // Create a target speed that fluctuates naturally
//    float targetSpeed = 60.0f + (50.0f * sinf(tickCounter * 0.01f));
//
//    // Smoothly approach target speed (Simple inertia)
//    if(currentSpeed < targetSpeed) {
//        currentSpeed += 0.5f; // Accelerating
//        accelPedal.setValue(80); // Pedal pressed
//        brakePedal.setValue(0);  // Brake released
//    } else {
//        currentSpeed -= 0.8f; // Decelerating
//        accelPedal.setValue(0);  // Pedal released
//        brakePedal.setValue(50); // Brake pressed (Regen)
//    }
//
//    // Clamp speed
//    if(currentSpeed < 0) currentSpeed = 0;
//    if(currentSpeed > 240) currentSpeed = 240;
//
//    // Update Speedometer
//    speedo.setValue((int)currentSpeed);
//    Unicode::snprintf(linearSpeedBuffer, LINEARSPEED_SIZE, "%d", (int)currentSpeed);
//	linearSpeed.invalidate();
//
//
//    // ==========================================
//    // 3. BATTERY SOC (Regen vs Drain)
//    // ==========================================
//    if (accelPedal.getValue() > 0)
//    {
//        // Discharging (Consumption)
//        currentSoc -= 0.01f;
//    }
//    else if (brakePedal.getValue() > 0)
//    {
//        // Regenerative Braking (Charging)
//        currentSoc += 0.05f;
//    }
//
//    // Keep SOC within 0-100
//    if (currentSoc > 100.0f) currentSoc = 100.0f;
//    if (currentSoc < 0.0f) currentSoc = 0.0f;
//
//    // Update Battery Widget (Visual Bar)
//    batteryState.setValue((int)currentSoc);
//
//    // Update Text Area (Digital Number)
//    // We cast to int to remove decimals for the display
//    Unicode::snprintf(socBuffer, SOC_SIZE, "%d", (int)currentSoc);
//    soc.invalidate();
//}

void Screen1View::handleTickEvent(){
	tickCounter++;

	bool isOnPhase = (tickCounter % 60) < 30;

	if (canLeftActive)
	{
		if(isOnPhase) {
			leftIndicator.setBitmap(BITMAP_LEFTINDICATOR_LIT_ID);
		} else {
			leftIndicator.setBitmap(BITMAP_LEFTINDICATOR_UNLIT_ID);
		}
	}
	leftIndicator.invalidate(); // Crucial: tell screen to redraw

	if (canRightActive)
	{
		if(isOnPhase) {
			rightIndicator.setBitmap(BITMAP_RIGHTINDICATOR_LIT_ID);
		} else {
			rightIndicator.setBitmap(BITMAP_RIGHTINDICATOR_UNLIT_ID);
		}
	}
	rightIndicator.invalidate();

	if(milActive) {
		if(isOnPhase) {
			mil.setBitmap(BITMAP_MILALTERNATE_ID);
		} else {
			mil.setBitmap(BITMAP_MILINACTIVE_ID);
		}
	}
	mil.invalidate();
}
