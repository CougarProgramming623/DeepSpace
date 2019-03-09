
#include "OI.h"
#include <frc/DriverStation.h>
#include "Cob.h"
#include "commands/SetForkPosition.h"
#include "commands/Turn.h"
#include "commands/ModeSwitch.h"

#include "commands/ClimbUp.h"
#include "commands/ClimbDown.h"

#include "commands/SetArmWristPosition.h"
#include "commands/SetServo.h"

#include "commands/TurnOnVacuum.h"
#include "commands/StopVacuum.h"

#include "commands/SetManipulator.h"

namespace frc2019 {

//Instantiate the Joystick and Button Board
frc::Joystick OI::driverJoystick = frc::Joystick(0);
frc::Joystick OI::buttonBoard = frc::Joystick(1);

OI::OI() : 
vacuumToggle(&buttonBoard, 1),
climbUp(&buttonBoard, 2), climbDown(&buttonBoard, 3),
egOverride(&buttonBoard, 4), driveOverride(&buttonBoard, 5), armOverride(&buttonBoard, 6), forkOverride(&buttonBoard, 7), wristOverride(&buttonBoard, 8),
turnTo0(&buttonBoard, 13), turnTo45(&buttonBoard, 14), turnTo90(&buttonBoard, 15), turnTo135(&buttonBoard, 16), turnTo180(&buttonBoard, 9), turnTo225(&buttonBoard, 10), turnTo270(&buttonBoard, 11), turnTo315(&buttonBoard, 12), 
toggleHatchCargo(&buttonBoard, 19),
forkGround(&buttonBoard, 20), forkUp(&buttonBoard, 21), forkStow(&buttonBoard, 22), forkHerd(&buttonBoard, 23),
cargoPickup(&buttonBoard, 25), low(&buttonBoard, 26), medium(&buttonBoard, 27), high(&buttonBoard, 28), ship(&buttonBoard, 29), allIn(&buttonBoard, 24),
fodToggle(&driverJoystick, 1)
{
	cargoMode = false;
	vacuumToggle.WhileHeld(new TurnOnVacuum());
	vacuumToggle.WhenReleased(new StopVacuum());
	climbUp.WhileHeld(new ClimbUp());
	climbDown.WhileHeld(new ClimbDown());
	driveOverride.WhenPressed(new BooleanToggle(&driveWithPercentOutput, [](bool newValue) {
		DriverStation::ReportError("Driving with percent output: " + newValue ? "true" : "false");
	}));
	armOverride.WhenPressed(new BooleanToggle(&useArmSlider, [](bool newValue) {
		DriverStation::ReportError("Using arm slider: " + newValue ? "true" : "false");
	}));
	forkOverride.WhenPressed(new BooleanToggle(&useForkSlider, [](bool newValue) {
		DriverStation::ReportError("Using Fork Slider: " + newValue ? "true" : "false");
	}));
	wristOverride.WhenPressed(new BooleanToggle(&useWristSlider, [](bool newValue) {
		DriverStation::ReportError("Using Wrist Slider: " + newValue ? "true" : "false");
	}));
	turnTo0.WhenPressed(new Turn(0.0));
	turnTo45.WhenPressed(new Turn(45));
	turnTo90.WhenPressed(new Turn(90));
	turnTo135.WhenPressed(new Turn(135));
	turnTo180.WhenPressed(new Turn(180));
	turnTo225.WhenPressed(new Turn(-135));
	turnTo270.WhenPressed(new Turn(-90));
	turnTo315.WhenPressed(new Turn(-45));
	/*
	toggleHatchCargo.WhileHeld(new ModeSwitch(&cargoMode, true, [](bool newValue) {
		DriverStation::ReportError("Cargo Mode: " + newValue ? "true" : "false");
		//Robot::vacuum->SetServoPosition(0.0);
	}));
	toggleHatchCargo.WhenReleased(new ModeSwitch(&cargoMode, false, [](bool newValue) {
		DriverStation::ReportError("Cargo Mode: " + newValue ? "true" : "false");
		//Robot::vacuum->SetServoPosition(1.0);
	}));
	*/

	forkStow.WhenPressed(new SetForkPosition(114));
	forkUp.WhenPressed(new SetForkPosition(267));
	forkGround.WhenPressed(new SetForkPosition(478));
	allIn.WhenPressed(new SetArmWristPosition(RocketHeight::ALL_IN));
	cargoPickup.WhileHeld(new SetArmWristPosition(RocketHeight::CARGO_PICKUP));
	low.WhileHeld(new SetArmWristPosition(IsCargoMode() ? RocketHeight::LOW_CARGO : RocketHeight::LOW_HATCH));
	medium.WhileHeld(new SetArmWristPosition(IsCargoMode() ? RocketHeight::MEDIUM_CARGO : RocketHeight::MEDIUM_HATCH));
	high.WhileHeld(new SetArmWristPosition(IsCargoMode() ? RocketHeight::HIGH_CARGO : RocketHeight::HIGH_HATCH));
	ship.WhileHeld(new SetArmWristPosition(IsCargoMode() ? RocketHeight::SHIP_CARGO : RocketHeight::LOW_HATCH));

	fodToggle.WhenPressed(new BooleanToggle(&fod, [](bool newValue) {
		DriverStation::ReportError("FOD: " + newValue ? "true" : "false");
	}));
} //OI()

void OI::Update() {
	cargoMode = buttonBoard.GetRawButton(19);
} //Update()

SliderStatus OI::GetSliderMode() {
	return sliderMode;
} //GetSliderMode()

bool OI::IsFOD() {
	return fod;
} //IsFOD()

bool OI::IsPercentOutputMode() {
	return driveWithPercentOutput;
}

bool OI::UsingArmSlider() {
	return useArmSlider;
}

bool OI::UsingForkSlider() {
	return useForkSlider;
}

bool OI::UsingWristSlider() {
	return useWristSlider;
}

bool OI::IsCargoMode() {
	return cargoMode;
}
}//frc2019
