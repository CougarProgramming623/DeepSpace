
#include "OI.h"
#include "OIConstants.h"
#include <frc/DriverStation.h>
#include "commands/PositveAngleTurnTest.h"
#include "commands/SetForkPosition.h"
namespace frc2019 {

//Instantiate the Joystick and Button Board
frc::Joystick OI::driverJoystick = frc::Joystick(0);
frc::Joystick OI::buttonBoard = frc::Joystick(1);

OI::OI() : 
	low(&buttonBoard, OI_ARM_POSITION_LOW), 
	medium(&buttonBoard, OI_ARM_POSITION_MEDUIM), 
	high(&buttonBoard, OI_ARM_POSITION_HIGH), 
	cargoHold(&buttonBoard, OI_ARM_POSITION_CARGO_HOLD), 
	cargoGround(&buttonBoard, OI_ARM_POSITION_CARGO_GROUND),
	manualControlOverride(&buttonBoard, OI_ARM_MANUAL_MODE), 
	vMode(&buttonBoard, OI_ARM_V_MODE), 
	fodToggle(&driverJoystick, 1)
	{
		fodToggle.WhenPressed(new BooleanToggle(&fod, [](bool newValue) {
			frc::DriverStation::ReportError(std::string("LAMBDA TEST FOD: ") + (newValue ? "true" : "false"));
		}));

		low.WhenPressed(new SetForkPosition(200));
		low.WhenPressed(new SetForkPosition(0));		
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
