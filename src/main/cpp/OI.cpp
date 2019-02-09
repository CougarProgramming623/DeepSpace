
#include "OI.h"

namespace frc2019 {


OI::OI() : 
	driverJoystick(new frc::Joystick(0)),
	buttonBoard(new frc::Joystick(1)),
	low(buttonBoard.get(), OI_ARM_POSITION_LOW), 
	medium(buttonBoard.get(), OI_ARM_POSITION_MEDUIM), 
	high(buttonBoard.get(), OI_ARM_POSITION_HIGH), 
	cargoHold(buttonBoard.get(), OI_ARM_POSITION_CARGO_HOLD), 
	cargoGround(buttonBoard.get(), OI_ARM_POSITION_CARGO_GROUND),
	manualControlOverride(buttonBoard.get(), OI_ARM_MANUAL_MODE), 
	vMode(buttonBoard.get(), OI_ARM_V_MODE), 
	fodToggle(buttonBoard.get(), OI_DRIVE_FOD_TOGGLE)
	{
		fodToggle.WhenPressed(new BooleanToggle(&fod));
	}


void OI::Update() {

}

SliderStatus OI::getSliderMode() {
	return sliderMode;
}


std::shared_ptr<frc::Joystick> OI::GetDriverJoystick() {
	return driverJoystick;
}

std::shared_ptr<frc::Joystick> OI::GetButtonBoard() {
	return buttonBoard;
}

bool OI::IsFOD() {
	return fod;
}

}//namespace
