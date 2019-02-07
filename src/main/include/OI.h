#pragma once
#include <frc/WPILib.h>

namespace frc2019 {

enum SliderStatus {
	DIAL_CONTROL, MANUAL_PID_CONTROL, VELOCITY_CONTROL
};

#define OI_ARM_POSITION_LOW 1
#define OI_ARM_POSITION_MEDUIM 2
#define OI_ARM_POSITION_HIGH 9

#define OI_ARM_POSITION_CARGO_HOLD 3
#define OI_ARM_POSITION_CARGO_GROUND 10

#define OI_ARM_MANUAL_MODE 8
#define OI_ARM_V_MODE 9


#define OI_ARM_POSITION_SLIDER 1
#define OI_WRIST_POSITION_SLIDER 2


class OI {

private:
	SliderStatus sliderMode = SliderStatus::DIAL_CONTROL;

	std::shared_ptr<frc::Joystick> driverJoystick;
	std::shared_ptr<frc::Joystick> buttonBoard;

	//Dial buttons
	frc::JoystickButton low, medium, high, cargoHold, cargoGround;
	//Arm Control Overrides
	frc::JoystickButton manualControlOverride, vMode;
	
public:
	OI();
	void Update();
	SliderStatus getSliderMode();
	
	std::shared_ptr<frc::Joystick> GetDriverJoystick();
	std::shared_ptr<frc::Joystick> GetButtonBoard();

};


}//namespace