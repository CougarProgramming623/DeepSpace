#pragma once

#define USE_PREVIOUS_BUTTONS

#ifdef USE_PREVIOUS_BUTTONS
	#define INTAKE_BUTTON 1
	#define EXPUNGE_BUTTON 2
	#define TOGGLE_SLIDER_BUTTON 3
	#define RELEASE_SHAFT_BUTTON 4
	#define RELEASE_RAMP_BUTTON 9
	#define TOGGLE_POT_BUTTON 8
	#define ENDGAME_OVERRIDE_BUTTON 5
	#define CLIMB_BUTTON 6
	#define POT_REZERO_BUTTON 7

	#define CLIMB_LED 1
	#define ZERO_BOTTOM_LED 2

	#define TOGGLE_PID_LED 3
	#define TOGGLE_SLIDER_LED 4
#endif


#include "WPILib.h"

namespace frc2019 {

enum SliderStatus {
	DIAL_CONTROL, MANUAL_PID_CONTROL, VELOCITY_CONTROL
};

class OI {
private:
	SliderStatus status;

	std::shared_ptr<frc::Joystick> driverJoystick;
	std::shared_ptr<frc::Joystick> buttonBoard;
	std::shared_ptr<frc::JoystickButton> intakeButton;
	std::shared_ptr<frc::JoystickButton> expungeButton;
	std::shared_ptr<frc::JoystickButton> toggleSliderControl;
	std::shared_ptr<frc::JoystickButton> togglePot;

	std::shared_ptr<frc::JoystickButton> releaseShaftButton;
	std::shared_ptr<frc::JoystickButton> releaseRampButton;

	std::shared_ptr<frc::JoystickButton> endgameOverride;
	std::shared_ptr<frc::JoystickButton> climb;
	std::shared_ptr<frc::JoystickButton> potRezeroLift;

public:
	OI();
	void Update();
	
	std::shared_ptr<frc::Joystick> GetDriverJoystick();
	std::shared_ptr<frc::Joystick> GetButtonBoard();

};


}//namespace