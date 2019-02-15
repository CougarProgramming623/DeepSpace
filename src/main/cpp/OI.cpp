
#include "OI.h"
#include <frc/DriverStation.h>
#include "commands/PositveAngleTurnTest.h"


namespace frc2019 {

//Instantiate the Joystick and Button Board
frc::Joystick OI::driverJoystick = frc::Joystick(0);
frc::Joystick OI::buttonBoard = frc::Joystick(1);

OI::OI() : 
	low(&buttonBoard, OI_ARM_POSITION_LOW), 
	medium(&buttonBoard, OI_ARM_POSITION_MEDUIM), 
	high(&buttonBoard, OI_ARM_POSITION_HIGH), 
	groundPickup(&buttonBoard, OI_ARM_POSITION_GROUND_PICKUP),
	secure(&buttonBoard, OI_ARM_POSITION_SECURE), 
	cargoShip(&buttonBoard, OI_ARM_POSITION_CARGO_SHIP),
	manualControlOverride(&buttonBoard, OI_ARM_MANUAL_MODE), 
	climb(&buttonBoard, OI_CLIMB), 
	vMode(&buttonBoard, OI_ARM_V_MODE), 
	fod(&buttonBoard, OI_DRIVE_FOD),
	cargoVsHatch(&buttonBoard, OI_CARGO_VS_HATCH),
	frontPickup(&buttonBoard, OI_FRONT_PICKUP),
	vacuum(&buttonBoard, OI_VACUUM),
	alleyOop(&buttonBoard, OI_ALLEY_OOP)
	{
		fod.WhenPressed(new BooleanToggle(&fodBool, [](bool newValue) {
			frc::DriverStation::ReportError(std::string("LAMBDA TEST FOD: ") + (newValue ? "true" : "false"));
		}));
		vacuum.WhenPressed(new BooleanToggle(&vacuumBool, [](bool newValue) {
			//Report to cob
		}));

		vMode.WhenPressed(new PositveAngleTurnTest());
		low.WhenPressed(new VariableSet(&dialMode, DialStatus::ROCKET_LOW, [](DialStatus newValue) {  /*TODO Cob Stuff*/ }));
		medium.WhenPressed(new VariableSet(&dialMode, DialStatus::ROCKET_MED, [](DialStatus newValue) {  /*TODO Cob Stuff*/ }));
		high.WhenPressed(new VariableSet(&dialMode, DialStatus::ROCKET_HIGH, [](DialStatus newValue) {  /*TODO Cob Stuff*/ }));

		groundPickup.WhenPressed(new VariableSet(&dialMode, DialStatus::GROUND_PICKUP, [](DialStatus newValue) {  /*TODO Cob Stuff*/ }));
		secure.WhenPressed(new VariableSet(&dialMode, DialStatus::SECURE, [](DialStatus newValue) {  /*TODO Cob Stuff*/ }));
		cargoShip.WhenPressed(new VariableSet(&dialMode, DialStatus::CARGO_SHIP, [](DialStatus newValue) {  /*TODO Cob Stuff*/ }));
	}


void OI::Update() {
	//Set vacuum led based on weather or not it is on
}

SliderStatus OI::getSliderMode() {
	return sliderMode;
}

bool OI::IsFOD() {
	return fodBool;
}

}//namespace
