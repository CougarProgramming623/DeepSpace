
#include "OI.h"
#include <frc/DriverStation.h>
#include "Cob.h"
#include "commands/SetForkPosition.h"
#include "commands/Drive.h"
#include "commands/ModeSwitch.h"
#include "commands/SetArmPosition.h"
#include "commands/SetServo.h"

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

		low.WhenPressed(new SetArmPosition(0));
		medium.WhenPressed(new SetArmPosition(80));
		cargoHold.WhenPressed(new SetArmPosition(80*2));

		arm.WhenPressed(new SetArmPosition(80*3));
		//wrist.WhenPressed(new SetArmPosition(80*4));
		//pickup.WhenPressed(new SetArmPosition(80*5));
		//max 445

		wrist.WhenPressed(new SetServo(0.5));
		pickup.WhenPressed(new SetServo(1.0));


		cargoGround.WhenPressed(new ModeSwitch(&isCargoMode, false, [](bool newValue) {
			Cob::PushValue(COB_HATCH, newValue);
		}));
} //OI()

void OI::Update() {

} //Update()

SliderStatus OI::GetSliderMode() {
	return sliderMode;
} //GetSliderMode()

bool OI::IsFOD() {
	return fod;
} //IsFOD()
}//frc2019
