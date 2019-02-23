
#include "OI.h"
#include "OIConstants.h"
#include <frc/DriverStation.h>
#include "commands/PositveAngleTurnTest.h"
#include "Cob.h"
#include "commands/SetForkPosition.h"
#include "commands/Drive.h"
#include "commands/ModeSwitch.h"

namespace frc2019 {

//Instantiate the Joystick and Button Board
frc::Joystick OI::driverJoystick = frc::Joystick(0);
frc::Joystick OI::buttonBoard = frc::Joystick(1);

bool OI::isCargoMode;

OI::OI() : 
	low(&buttonBoard, OI_ARM_POSITION_LOW), 
	medium(&buttonBoard, OI_ARM_POSITION_MEDUIM), 
	high(&buttonBoard, OI_ARM_POSITION_HIGH), 
	cargoHold(&buttonBoard, OI_ARM_POSITION_CARGO_HOLD), 
	cargoGround(&buttonBoard, OI_ARM_POSITION_CARGO_GROUND),
	manualControlOverride(&buttonBoard, OI_ARM_MANUAL_MODE), 
	vMode(&buttonBoard, OI_ARM_V_MODE), 
	fodToggle(&driverJoystick, 1), 
	arm(&buttonBoard, 4),
	wrist(&buttonBoard, 5),
	pickup(&buttonBoard, 6)
	{
		fodToggle.WhenPressed(new BooleanToggle(&fod, [](bool newValue) {
			Cob::PushValue(COB_FIELD_ORIENTED, newValue);
		}));
	
		low.WhenPressed(new SetForkPosition(300));
		medium.WhenPressed(new SetForkPosition(0));
		high.WhenPressed(new SetForkPosition(150));

		cargoHold.WhenPressed(new ModeSwitch(&isCargoMode, true));
		cargoGround.WhenPressed(new ModeSwitch(&isCargoMode, false));
	}



void OI::Update() {
}

SliderStatus OI::getSliderMode() {
	return sliderMode;
}

bool OI::IsFOD() {
	return fod;
}

}//namespace
