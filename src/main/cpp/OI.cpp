
#include "OI.h"
#include <frc/DriverStation.h>
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
	fodToggle(&driverJoystick, 1)
	{
		fodToggle.WhenPressed(new BooleanToggle(&fod, [](bool newValue) {
			// frc::DriverStation::ReportError(std::string("LAMBDA TEST FOD: ") + (newValue ? "true" : "false"));
			Cob::PushValue(COB_FIELD_ORIENTED,newValue);
		}));

		low.WhenPressed(new SetForkPosition(1453));
		medium.WhenPressed(new SetForkPosition(1122));
		high.WhenPressed(new SetForkPosition((1453+1122)/2));

		cargoHold.WhenPressed(new ModeSwitch(&isCargoMode, true, [](bool newValue) {
			Cob::PushValue(COB_HATCH, newValue);
		}));

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
}//namespace
