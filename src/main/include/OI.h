#pragma once
#include <frc/WPILib.h>
#include "commands/BooleanToggle.h"
#include "GameEnums.h"
#include "RobotConstants.h"
#include "OIConstants.h"


namespace frc2019 {

class OI {
public:
	static frc::Joystick driverJoystick;
	static frc::Joystick buttonBoard;
	int anglePos = 0;//For easy access in lambda command

private:
	SliderStatus sliderMode = SliderStatus::DIAL_CONTROL;

	frc::JoystickButton vacuumToggle;
	frc::JoystickButton climbUp, climbDown, endgameOverride, driveOverride;
	frc::JoystickButton armOverride, spoonOverride, wristOverride;
	frc::JoystickButton a0, a1, a2, a3, a4, a5, a6, a7;
	frc::JoystickButton	toggleHatchCargo;
	frc::JoystickButton spoonGround, spoonScoop, spoonCargo, spoonVertical;
	frc::JoystickButton allIn, pickup, low, medium, high, ship;
	frc::JoystickButton fodToggle;

	bool fod;
	bool driveWithPercentOutput;
	bool useArmSlider, useSpoonSlider, useWristSlider;
	bool lastButtonVal = false;

	/*
	//Dial buttons
	frc::JoystickButton low, medium, high, cargoHold, cargoGround;
	//Arm Control Overrides
	frc::JoystickButton manualControlOverride, vMode;
	//Drive Control Overrids
	//temporary individual motor buttons
	frc::JoystickButton arm;
	frc::JoystickButton wrist;
	frc::JoystickButton pickup;
	frc::JoystickButton climb;
	*/
	
public:
	OI();
	void Update();
	SliderStatus GetSliderMode();
	inline bool IsAlignmentMode() { 
		return !IsFOD();
	}
	bool CanClimb();
	bool IsFOD();
	bool IsPercentOutputMode();
	bool UsingArmSlider();
	bool UsingSpoonSlider();
	bool UsingWristSlider();
	bool GetVision();
	CargoOrHatch IsCargoMode();
	bool IsVisionActive();
	inline int GetAnglePos() { return anglePos; }
};

}//frc2019
