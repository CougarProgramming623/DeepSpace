#pragma once
#include <frc/WPILib.h>
#include "commands/BooleanToggle.h"
#include "GameEnums.h"
#include "OIConstants.h"


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
	
public:
	OI();
	void Update();
	SliderStatus getSliderMode();
	inline bool IsAlignmentMode() { 
		return !IsFOD(); 
	}
	bool IsFOD();
	static bool isCargoMode;
};

}//namespace