
#include "OI.h"
#include <frc/DriverStation.h>
#include "Cob.h"
#include "commands/SetForkPosition.h"
#include "commands/Turn.h"
#include "commands/ModeSwitch.h"
#include "commands/ReadDIO.h"

#include "commands/ClimbUp.h"
#include "commands/ClimbDown.h"

#include "commands/SetArmWristPosition.h"
#include "commands/SetArmWristPositionSecure.h"
#include "commands/SetServo.h"

#include "commands/TurnOnVacuum.h"
#include "commands/StopVacuum.h"

#include "commands/VisionDrive.h"

#include "commands/SetManipulator.h"
#include "commands/LambdaCommand.h"

#include "GameEnums.h"
#include "Constants.h"
#include "RobotConstants.h"

#include "commands/VisionDrive.h"
#include "commands/CargoHatchModeSwitch.h"

#define ARM_AXIS 1
#define FORK_AXIS 2
#define WRIST_AXIS 3


namespace frc2019 {

//Instantiate the Joystick and Button Board
frc::Joystick OI::driverJoystick = frc::Joystick(0);
frc::Joystick OI::buttonBoard = frc::Joystick(1);

#define ARM_OVERRIDE 6
#define FORK_OVERRIDE 7
#define WRIST_OVERRIDE 8

#define CARGO_HATCH_TOGGLE 19

OI::OI() : 
vacuumToggle(&buttonBoard, 1),
climbUp(&buttonBoard, 2), climbDown(&buttonBoard, 3), endgameOverride(&buttonBoard, 4), driveOverride(&buttonBoard, 5),
armOverride(&buttonBoard, ARM_OVERRIDE), forkOverride(&buttonBoard, FORK_OVERRIDE), wristOverride(&buttonBoard, WRIST_OVERRIDE),
turnTo0(&buttonBoard, 13), turnTo45(&buttonBoard, 14), turnTo90(&buttonBoard, 15), turnTo135(&buttonBoard, 16), turnTo180(&buttonBoard, 9), turnTo225(&buttonBoard, 10), turnTo270(&buttonBoard, 11), turnTo315(&buttonBoard, 12), 
toggleHatchCargo(&buttonBoard, CARGO_HATCH_TOGGLE),
forkGround(&buttonBoard, 20), forkUp(&buttonBoard, 21), forkStow(&buttonBoard, 22), forkHerd(&buttonBoard, 23),
allIn(&buttonBoard, 24), pickup(&buttonBoard, 25), low(&buttonBoard, 26), ship(&buttonBoard, 27), medium(&buttonBoard, 28), high(&buttonBoard, 29),
fodToggle(&driverJoystick, 1)
{
	vacuumToggle.WhenPressed(new TurnOnVacuum());
	vacuumToggle.WhenReleased(new StopVacuum());
	toggleHatchCargo.WhenPressed(new CargoHatchModeSwitch(true));
	toggleHatchCargo.WhenReleased(new CargoHatchModeSwitch(false));
	climbUp.WhileHeld(new ClimbUp());
	climbDown.WhileHeld(new ClimbDown());
	driveOverride.WhenPressed(new BooleanToggle(&driveWithPercentOutput, [](bool newValue) {
		DriverStation::ReportError("Driving with percent output: " + newValue ? "true" : "false");
	}));
	turnTo0.WhenPressed(new Turn(0.0f));
	turnTo45.WhenPressed(new Turn(28.77f));
	turnTo90.WhenPressed(new Turn(90.0f));
	turnTo135.WhenPressed(new Turn(151.23f));
	turnTo180.WhenPressed(new Turn(180));
	turnTo225.WhenPressed(new Turn(-151.23f));
	turnTo270.WhenPressed(new Turn(-90.0f));
	turnTo315.WhenPressed(new Turn(-28.77f));

	forkStow.WhenPressed(new SetForkPosition(114));
	forkUp.WhenPressed(new SetForkPosition(267));
	forkGround.WhenPressed(new SetForkPosition(478));

	armOverride.WhenReleased(new LambdaCommand([]() {
		Robot::arm->SetVelocity(0.0f);
	}));
	forkOverride.WhenReleased(new LambdaCommand([]() {
		Robot::fork->SetVelocity(0.0f);
	}));
	wristOverride.WhenReleased(new LambdaCommand([]() {
		Robot::wrist->SetVelocity(0.0f);
	}));

	//allIn.WhileHeld(new SetArmWristPositionSecure(DialPosition::ALL_IN));
	allIn.WhenPressed(new SetArmWristPositionSecure(DialPosition::ALL_IN));
	pickup.WhenPressed(new SetArmWristPosition(DialPosition::PICKUP));
	low.WhenPressed(new SetArmWristPosition(DialPosition::LOW));
	ship.WhenPressed(new SetArmWristPosition(DialPosition::SHIP));
	medium.WhenPressed(new SetArmWristPosition(DialPosition::MEDIUM));
	high.WhenPressed(new SetArmWristPosition(DialPosition::HIGH));
	fodToggle.WhenPressed(new VisionDrive());
	
	DriverStation::ReportError("OI DOne");
} //OI()

static bool lastButton = false;

void OI::Update() {
	if (UsingArmSlider()) {
		Robot::arm->SetVelocity(buttonBoard.GetRawAxis(0));// The value is already [-1, 1]
	}

	if(UsingForkSlider()) {
		Robot::fork->SetVelocity(buttonBoard.GetRawAxis(1));
	}
	
	if(UsingWristSlider()) {
		Robot::wrist->SetVelocity(buttonBoard.GetRawAxis(2));
	}

	bool currentButton = driverJoystick.GetRawButton(1);
	//DriverStation::ReportError(std::string("c: ") + (currentButton ? "true" : "false") + " last " + (lastButton ? "true" : "false"));
	if (currentButton && !lastButton) {
		if(fod) {
			fod = false;
			DriverStation::ReportError("FOD Drive Off");
			Cob::PushValue(COB_FIELD_ORIENTED, false);
		} else {
			fod = true;
			DriverStation::ReportError("FOD Drive On");
			Cob::PushValue(COB_FIELD_ORIENTED, true);
		}
	}
	lastButton = currentButton;
	/*
	if(buttonBoard.GetRawButton(19)) {
		Robot::vacuum->SetServoPosition(0);
	} else {
		Robot::vacuum->SetServoPosition(0.65);
	}
	*/
} //Update()

SliderStatus OI::GetSliderMode() {
	return sliderMode;
} //GetSliderMode()


bool OI::CanClimb() {
	bool isTeleop = frc::DriverStation::GetInstance().IsOperatorControl();
	double time = frc::DriverStation::GetInstance().GetMatchTime();
	bool endgameOverrideSwitch = endgameOverride.Get();
	return (isTeleop && time < 35.0 && time > 0.0) || endgameOverrideSwitch;
}
bool OI::IsFOD() {
	return fod;
} //IsFOD()

bool OI::IsPercentOutputMode() {
	return driveWithPercentOutput;
}

bool OI::UsingArmSlider() {
	return buttonBoard.GetRawButton(ARM_OVERRIDE);
}

bool OI::UsingForkSlider() {
	return buttonBoard.GetRawButton(FORK_OVERRIDE);
}

bool OI::UsingWristSlider() {
	return buttonBoard.GetRawButton(WRIST_OVERRIDE);
}

CargoOrHatch OI::IsCargoMode() {
	return (buttonBoard.GetRawButton(CARGO_HATCH_TOGGLE) ? CargoOrHatch::HATCH : CargoOrHatch::CARGO);
}

bool OI::IsVisionActive(){
	return driverJoystick.GetRawButton(1);
}

}//frc2019
