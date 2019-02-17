#pragma once
#include <frc/WPILib.h>
#include "commands/BooleanToggle.h"
#include "commands/SetArmPosition.h"
#include "GameEnums.h"
#include "RobotConstants.h"

namespace frc2019 {

class OI {
public:
	static frc::Joystick driverJoystick;
	static frc::Joystick buttonBoard;

private:
	SliderStatus sliderMode = SliderStatus::DIAL_CONTROL;

	//Dial buttons
	frc::JoystickButton low, medium, high, cargoHold, cargoGround;
	//Arm Control Overrides
	frc::JoystickButton manualControlOverride, vMode;
	//Drive Control Overrids
	frc::JoystickButton fodToggle;
	bool fod;
	//temporary individual motor buttons
	frc::JoystickButton arm;
	frc::JoystickButton wrist;
	frc::JoystickButton pickup;
	
public:
	OI();
	void Update();
	SliderStatus getSliderMode();
	inline bool IsAlignmentMode() { 
		return !IsFOD(); 
	}
	bool IsFOD();
};

}//namespace