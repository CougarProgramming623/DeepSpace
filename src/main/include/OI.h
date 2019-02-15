#pragma once
#include <frc/WPILib.h>
#include "commands/BooleanToggle.h"
#include "commands/VariableSet.h"
#include "GameEnums.h"

namespace frc2019 {

#define OI_ARM_POSITION_LOW 1
#define OI_ARM_POSITION_MEDUIM 2
#define OI_ARM_POSITION_HIGH 9

#define OI_ARM_POSITION_CARGO_SHIP 3
#define OI_ARM_POSITION_GROUND_PICKUP 10
#define OI_ARM_POSITION_SECURE -1

#define OI_DRIVE_FOD 1
#define OI_DRIVE_ALIGN 7

#define OI_ARM_MANUAL_MODE 9
#define OI_ARM_V_MODE 8

#define OI_ARM_POSITION_SLIDER 1
#define OI_WRIST_POSITION_SLIDER 2

#define OI_CLIMB -1

#define OI_CARGO_VS_HATCH -1
#define OI_FRONT_PICKUP -1
#define OI_VACUUM -1
#define OI_ALLEY_OOP -1

class OI {
public:
	static frc::Joystick driverJoystick;
	static frc::Joystick buttonBoard;

private:
	SliderStatus sliderMode = SliderStatus::DIAL_CONTROL;
	DialStatus dialMode = DialStatus::SECURE;

	//Dial buttons
	frc::JoystickButton low, medium, high, groundPickup, secure, cargoShip;
	//Arm Control Overrides
	frc::JoystickButton manualControlOverride, vMode;
	//Drive Control Overrids
	frc::JoystickButton fod, climb;

	frc::JoystickButton cargoVsHatch, frontPickup, vacuum, alleyOop;

	bool fodBool, vacuumBool;
	
public:
	OI();
	void Update();
	SliderStatus getSliderMode();
	
	std::shared_ptr<frc::Joystick> GetDriverJoystick();
	std::shared_ptr<frc::Joystick> GetButtonBoard();

	inline bool IsAlignmentMode() { return !IsFOD(); }
	bool IsFOD();
};


}//namespace