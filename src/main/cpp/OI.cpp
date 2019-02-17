
#include "OI.h"
#include "OIConstants.h"
#include <frc/DriverStation.h>
#include "commands/PositveAngleTurnTest.h"
#include "commands/ArmControl.h"
#include "commands/PickupControl.h"
#include "commands/WristControl.h"

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
	fodToggle(&driverJoystick, 1), 
	arm(&buttonBoard, 4),
	wrist(&buttonBoard, 5),
	pickup(&buttonBoard, 6)
	{
		fodToggle.WhenPressed(new BooleanToggle(&fod, [](bool newValue) {
			frc::DriverStation::ReportError(std::string("LAMBDA TEST FOD: ") + (newValue ? "true" : "false"));
		}));

		vMode.WhenPressed(new PositveAngleTurnTest());

		arm.WhileHeld(new ArmControl(.25));
		arm.WhenReleased(new ArmControl(0.0));
		manualControlOverride.WhileHeld(new ArmControl(-.25));
		manualControlOverride.WhenReleased( new ArmControl(0.0));
		wrist.WhileHeld(new WristControl());
		pickup.WhileHeld(new PickupControl());
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
