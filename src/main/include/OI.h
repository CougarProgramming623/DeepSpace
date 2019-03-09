#pragma once
#include <frc/WPILib.h>
#include "commands/BooleanToggle.h"
#include "commands/SetForkPosition.h"
#include "GameEnums.h"
#include "RobotConstants.h"
#include "OIConstants.h"


namespace frc2019 {

class OI {
public:
	static frc::Joystick driverJoystick;
	static frc::Joystick buttonBoard;

private:
	SliderStatus sliderMode = SliderStatus::DIAL_CONTROL;

	frc::JoystickButton vacuumToggle;
	frc::JoystickButton climbUp, climbDown;
	frc::JoystickButton egOverride, driveOverride, armOverride, forkOverride, wristOverride;
	frc::JoystickButton turnTo0, turnTo45, turnTo90, turnTo135, turnTo180, turnTo225, turnTo270, turnTo315;
	frc::JoystickButton	toggleHatchCargo;
	frc::JoystickButton forkGround, forkHerd, forkUp, forkStow;
	frc::JoystickButton allIn, cargoPickup, low, medium, high, ship;
	frc::JoystickButton fodToggle;
	bool fod;
	bool driveWithPercentOutput;
	bool useArmSlider, useForkSlider, useWristSlider;
	bool cargoMode = false;
	/*
	//Dial buttons
	frc::JoystickButton low, medium, high, cargoHold, cargoGround;
	//Arm Control Overrides
	frc::JoystickButton manualControlOverride, vMode;
	//Drive Control Overrids
	frc::JoystickButton fodToggle;
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
	bool IsFOD();
	bool IsPercentOutputMode();
	bool UsingArmSlider();
	bool UsingForkSlider();
	bool UsingWristSlider();
	bool IsCargoMode();
};

}//frc2019