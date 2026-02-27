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
	Unicode::snprintf(rangeBuffer, RANGE_SIZE, "%d", 0);
	range.invalidate();
	Unicode::snprintf(odoBuffer, ODO_SIZE, "%d", 0);
	odo.invalidate();
	Unicode::snprintf(steeringAngleBuffer, STEERINGANGLE_SIZE, "%d", 0);
	steeringAngle.invalidate();
	Unicode::snprintf(socBuffer, SOC_SIZE, "%d", 0);
	soc.invalidate();
	Unicode::fromUTF8((const uint8_t*)"ECO", driveModeBuffer, DRIVEMODE_SIZE);
	driveMode.invalidate();
	Unicode::snprintf(torquePower_FLBuffer1, TORQUEPOWER_FLBUFFER1_SIZE, "%d", 0);
	Unicode::snprintf(torquePower_FLBuffer2, TORQUEPOWER_FLBUFFER2_SIZE, "%d", 0);
	torquePower_FL.invalidate();
	Unicode::snprintf(torquePower_FRBuffer1, TORQUEPOWER_FRBUFFER1_SIZE, "%d", 0);
	Unicode::snprintf(torquePower_FRBuffer2, TORQUEPOWER_FRBUFFER2_SIZE, "%d", 0);
	torquePower_FR.invalidate();
	Unicode::snprintf(torquePower_RmBuffer1, TORQUEPOWER_RMBUFFER1_SIZE, "%d", 0);
	Unicode::snprintf(torquePower_RmBuffer2, TORQUEPOWER_RMBUFFER2_SIZE, "%d", 0);
	torquePower_Rm.invalidate();
	Unicode::snprintf(linearSpeedBuffer, LINEARSPEED_SIZE, "%d", 0);
	linearSpeed.invalidate();
	Unicode::snprintf(driveTrainStatusBuffer, DRIVETRAINSTATUS_SIZE, "%s", "IDLE");
	driveTrainStatus.invalidate();
	canLeftActive = false;
	canRightActive = false;
	milActive = false;
	parkBrake.setVisible(false);
}

void Screen1View::showDriverControls(DriverInputAndVehicleControl_t data) {
	accelPedal.setValue(data.Acc_Ped_Pos);
	accelPedal.invalidate();
	brakePedal.setValue(data.Brk_Ped_Pos);
	brakePedal.invalidate();

	char gearString = '-'; // Default if signal is invalid

	switch (data.PRND_State)
	{
	case 0: // CAN says 0 is Neutral
		gearString = 'N';
		parkBrake.setVisible(false);
		break;
	case 1: // CAN says 1 is Park
		gearString = 'P';
		parkBrake.setVisible(true);
		break;
	case 2: // CAN says 2 is Drive
		gearString = 'D';
		parkBrake.setVisible(false);
		break;
	case 3: // CAN says 3 is Reverse
		gearString = 'R';
		parkBrake.setVisible(false);
		break;
	default:
		gearString = '-'; // Error or invalid state
		parkBrake.setVisible(false);
		break;
	}

	Unicode::snprintf(textAreaPrndBuffer, TEXTAREAPRND_SIZE, "%c", gearString);
	textAreaPrnd.invalidate();
	parkBrake.invalidate();

	switch(data.Drv_Program) {
		case 0:
			Unicode::fromUTF8((const uint8_t*)"ECO", driveModeBuffer, DRIVEMODE_SIZE);
			break;
		case 1:
			Unicode::fromUTF8((const uint8_t*)"SPORT", driveModeBuffer, DRIVEMODE_SIZE);
			break;
		case 2:
			Unicode::fromUTF8((const uint8_t*)"SNOW", driveModeBuffer, DRIVEMODE_SIZE);
			break;
		default:
			Unicode::fromUTF8((const uint8_t*)"ECO", driveModeBuffer, DRIVEMODE_SIZE);
			break;
	}
	driveMode.invalidate();

	float steeringRad = data.StWhl_Angl_Act * (3.14159f / 180.0f); // angles are in °
	float wheelRad = data.Whl_Angl_Act * (3.14159f / 180.0f);

	Unicode::snprintfFloat(steeringAngleBuffer, STEERINGANGLE_SIZE, "%.1f", data.StWhl_Angl_Act);
	steeringAngle.invalidate();

	steeringWheel.updateZAngle(steeringRad);
	steeringWheel.invalidate();

	frontLeftWheel.updateZAngle(wheelRad);
	frontRightWheel.updateZAngle(wheelRad);

	// Invalidate tires to redraw
	frontLeftWheel.invalidate();
	frontRightWheel.invalidate();

	Unicode::snprintfFloat(wheelAngle_FLBuffer, WHEELANGLE_FL_SIZE, "%.1f",  data.Whl_Angl_Act);
	wheelAngle_FL.invalidate();
	Unicode::snprintfFloat(wheelAngle_FRBuffer, WHEELANGLE_FR_SIZE, "%.1f",  data.Whl_Angl_Act);
	wheelAngle_FR.invalidate();
}

void Screen1View::showSteering(DriverInputAndVehicleControl2_t data) {
	if(data.Sbw_Rack_Pos_Req != data.Sbw_Rack_Pos_Act) {
		frontLeftWheel.setBitmap(BITMAP_TYRE_ID);
	} else {
		frontLeftWheel.setBitmap(BITMAP_TYREINCORRECT_ID);
	}
}

void Screen1View::showPowertrainStatus(PowertrainStatusAndReadiness_t data) {
	if(data.MIL_Lamp_Status == 1) {
		milActive = true;
	} else {
		milActive = false;
	}

	switch(data.Turn_Indicator_State) {
		case 0:
			canLeftActive = false;
			canRightActive = false;
			hazardLight.setBitmap(BITMAP_HAZARDLIGHTINACTIVE_ID);
			hazardLight.invalidate();
			break;
		case 1:
			canLeftActive = true;
			canRightActive = false;
			hazardLight.setBitmap(BITMAP_HAZARDLIGHTINACTIVE_ID);
			hazardLight.invalidate();
			break;
		case 2:
			canLeftActive = false;
			canRightActive = true;
			hazardLight.setBitmap(BITMAP_HAZARDLIGHTINACTIVE_ID);
			hazardLight.invalidate();
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

	switch(data.PT_Ready) {
		case 0:
			powerTrainStatus.setBitmap(BITMAP_PTSTATUSNOTREADY_ID);
			powerTrainStatus.invalidate();
			break;
		case 1:
			powerTrainStatus.setBitmap(BITMAP_PTREADY_ID);
			powerTrainStatus.invalidate();
			break;
		default:
			powerTrainStatus.setBitmap(BITMAP_PTSTATUSNOTREADY_ID);
			powerTrainStatus.invalidate();
			break;
	}

	switch(data.DrvTrain_Status) {
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

void Screen1View::showMotorTorque1(Motor_And_Torque_Control_1_t data) {
	Unicode::snprintf(torquePower_FLBuffer1, TORQUEPOWER_FLBUFFER1_SIZE, "%d", data.Trq_Req_Wheel_FL);
	Unicode::snprintf(torquePower_FLBuffer2, TORQUEPOWER_FLBUFFER2_SIZE, "%d", data.Trq_Act_Wheel_FL);
	torquePower_FL.invalidate();

	Unicode::snprintf(torquePower_FRBuffer1, TORQUEPOWER_FRBUFFER1_SIZE, "%d", data.Trq_Req_Wheel_FR);
	Unicode::snprintf(torquePower_FRBuffer2, TORQUEPOWER_FRBUFFER2_SIZE, "%d", data.Trq_Act_Wheel_FR);
	torquePower_FR.invalidate();
}

void Screen1View::showMotorTorque2(Motor_And_Torque_Control_2_t data) {
	Unicode::snprintf(torquePower_RmBuffer1, TORQUEPOWER_FRBUFFER1_SIZE, "%d", data.Trq_Req_Wheel_RM);
	Unicode::snprintf(torquePower_RmBuffer2, TORQUEPOWER_FRBUFFER2_SIZE, "%d", data.Trq_Act_Wheel_RM);
	torquePower_Rm.invalidate();
}

void Screen1View::showEfficiency(Efficiency_Performance_1_t data) {
	Unicode::snprintf(optEffBuffer, ACTEFF_SIZE, "%d", data.Sys_Eff_Opt);
	Unicode::snprintf(actEffBuffer, OPTEFF_SIZE, "%d", data.Sys_Eff_Act);
	actEff.invalidate();
	optEff.invalidate();

	Unicode::snprintf(accelCharBuffer1, ACCELCHARBUFFER1_SIZE, "%d", data.LongAccel);
	Unicode::snprintf(accelCharBuffer2, ACCELCHARBUFFER2_SIZE, "%d", data.LatAccel);
	accelChar.invalidate();

	Unicode::snprintf(rangeBuffer, RANGE_SIZE, "%d", data.Rng_Rem);
	range.invalidate();
}

void Screen1View::showPressHydLightPt(Press_Hydraulic_Light_PowerTrain_t data) {
	Unicode::snprintf(presFrontBuffer1, PRESFRONTBUFFER1_SIZE, "%d", data.Pres_Susp_Front);
	Unicode::snprintf(presFrontBuffer2, PRESFRONTBUFFER2_SIZE, "%d", data.Pres_Brk_Front);
	presFront.invalidate();

	Unicode::snprintf(presRearBuffer1, PRESREARBUFFER1_SIZE, "%d", data.Pres_Susp_Rear);
	Unicode::snprintf(presRearBuffer2, PRESREARBUFFER2_SIZE, "%d", data.Pres_Brk_Rear);
	presFront.invalidate();

	if(data.LowBeam_St) {
		headlight.setBitmap(BITMAP_LOWBEAM_ID);
	} else if(data.HighBeam_St) {
		headlight.setBitmap(BITMAP_HIGHBEAM_ID);
	} else {
		headlight.setBitmap(BITMAP_HEADLIGHTSINACTIVE_ID);
	}
	headlight.invalidate();

	if(data.PosLight_St) {
		posLights.setBitmap(BITMAP_POSLIGHTSACTIVE_ID);
	} else if(!data.PosLight_St) {
		posLights.setBitmap(BITMAP_POSLIGHTSINACTIVE_ID);
	}
	posLights.invalidate();

	if(data.IntLight_St) {
		intLight.setBitmap(BITMAP_INTLIGHTACTIVE_ID);
	} else if(!data.IntLight_St) {
		intLight.setBitmap(BITMAP_INTLIGHTINACTIVE_ID);
	}
	intLight.invalidate();

	Unicode::snprintf(rmPowerBuffer, RMPOWER_SIZE, "%d", data.Pwr_Act_MotRM);
	rmPower.invalidate();
	Unicode::snprintf(power_FLBuffer, POWER_FL_SIZE, "%d", data.Pwr_Act_MotFL);
	power_FL.invalidate();
	Unicode::snprintf(power_FRBuffer, POWER_FR_SIZE, "%d", data.Pwr_Act_MotFR);
	power_FR.invalidate();
}

void Screen1View::showAux(Auxiliary_States_LV_SOC_t data) {
	switch(data.DCDC_State) {
		case 0:
			dcdcStatus.setBitmap(BITMAP_DCDCOFF_ID);
			break;
		case 1:
			dcdcStatus.setBitmap(BITMAP_DCDCPRECHARGE_ID);
			break;
		case 2:
			dcdcStatus.setBitmap(BITMAP_DCDCNORMAL_ID);
			break;
		case 3:
			dcdcStatus.setBitmap(BITMAP_DCDCERROR_ID);
			break;
		default:
			dcdcStatus.setBitmap(BITMAP_DCDCOFF_ID);
			break;
	}
	dcdcStatus.invalidate();

	switch(data.AirComp_State) {
		case 0:
			airCompStatus.setBitmap(BITMAP_AIRCOMPOFF_ID);
			break;
		case 1:
			airCompStatus.setBitmap(BITMAP_AIRCOMPPRESCHARGE_ID);
			break;
		case 2:
			airCompStatus.setBitmap(BITMAP_AIRCOMPNORMAL_ID);
			break;
		case 3:
			airCompStatus.setBitmap(BITMAP_AIRCOMPERROR_ID);
			break;
		default:
			airCompStatus.setBitmap(BITMAP_AIRCOMPOFF_ID);
			break;
	}
	airCompStatus.invalidate();

	switch(data.Heater_State) {
		case 0:
			heaterStatus.setBitmap(BITMAP_HEATEROFF_ID);
			break;
		case 1:
			heaterStatus.setBitmap(BITMAP_HEATERPRECHARGE_ID);
			break;
		case 2:
			heaterStatus.setBitmap(BITMAP_HEATERON_ID);
			break;
		case 3:
			heaterStatus.setBitmap(BITMAP_HEATERFAULT_ID);
			break;
		default:
			heaterStatus.setBitmap(BITMAP_HEATEROFF_ID);
			break;
	}
	heaterStatus.invalidate();

	batteryState.setValue(data.SOC_Batt_HV); // assuming the charge is in %
	Unicode::snprintf(socBuffer, SOC_SIZE, "%d", data.SOC_Batt_HV);
	soc.invalidate();
	batteryState.invalidate();

	Unicode::snprintf(hvBuffer, HV_SIZE, "%d", data.DCDC_HV_Voltage);
	hv.invalidate();
	Unicode::snprintf(lvBuffer, LV_SIZE, "%d", data.LV_Voltage);
	lv.invalidate();
}

void Screen1View::showVehicleState(VehicleState1_t data)  {
	speedo.setValue(data.Speed);
	speedo.invalidate();
    Unicode::snprintfFloat(linearSpeedBuffer, LINEARSPEED_SIZE, "%0.1f", data.Speed);
	linearSpeed.invalidate();

	Unicode::snprintf(odoBuffer, ODO_SIZE, "%df", data.Odometer);
	odo.invalidate();
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
