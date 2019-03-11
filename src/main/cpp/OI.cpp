
#include "OI.h"
#include <frc/DriverStation.h>
#include "Cob.h"
#include "commands/SetForkPosition.h"
#include "commands/Turn.h"
#include "commands/ModeSwitch.h"

#include "commands/ClimbUp.h"
#include "commands/ClimbDown.h"

#include "commands/SetArmWristPosition.h"
#include "commands/SetArmWristPositionSecure.h"
#include "commands/SetServo.h"

#include "commands/TurnOnVacuum.h"
#include "commands/StopVacuum.h"

#include "commands/SetManipulator.h"

#include "GameEnums.h"
#include "Constants.h"
#include "RobotConstants.h"

#define V_MODE_OVERRIDE 6
#define POSITION_OVERRIDE 8

#define ARM_AXIS 0
#define WRIST_AXIS 1

#define CARGO_HATCH_TOGGLE 19

namespace frc2019 {

//Instantiate the Joystick and Button Board
frc::Joystick OI::driverJoystick = frc::Joystick(0);
frc::Joystick OI::buttonBoard = frc::Joystick(1);

OI::OI() : 
vacuumToggle(&buttonBoard, 1),
climbUp(&buttonBoard, 2), climbDown(&buttonBoard, 3),
egOverride(&buttonBoard, 4), driveOverride(&buttonBoard, 5), vModeOverride(&buttonBoard, V_MODE_OVERRIDE), forkOverride(&buttonBoard, 7), positionOverride(&buttonBoard, POSITION_OVERRIDE),
turnTo0(&buttonBoard, 13), turnTo45(&buttonBoard, 14), turnTo90(&buttonBoard, 15), turnTo135(&buttonBoard, 16), turnTo180(&buttonBoard, 9), turnTo225(&buttonBoard, 10), turnTo270(&buttonBoard, 11), turnTo315(&buttonBoard, 12), 
toggleHatchCargo(&buttonBoard, CARGO_HATCH_TOGGLE),
forkGround(&buttonBoard, 20), forkUp(&buttonBoard, 21), forkStow(&buttonBoard, 22), forkHerd(&buttonBoard, 23),
allIn(&buttonBoard, 24), pickup(&buttonBoard, 25), low(&buttonBoard, 26), ship(&buttonBoard, 27), medium(&buttonBoard, 28), high(&buttonBoard, 29),
fodToggle(&driverJoystick, 1)
{
	vacuumToggle.WhileHeld(new TurnOnVacuum());
	vacuumToggle.WhenReleased(new StopVacuum());
	climbUp.WhileHeld(new ClimbUp());
	climbDown.WhileHeld(new ClimbDown());
	driveOverride.WhenPressed(new BooleanToggle(&driveWithPercentOutput, [](bool newValue) {
		DriverStation::ReportError("Driving with percent output: " + newValue ? "true" : "false");
	}));
	forkOverride.WhenPressed(new BooleanToggle(&useForkSlider, [](bool newValue) {
		DriverStation::ReportError("Using Fork Slider: " + newValue ? "true" : "false");
	}));
	turnTo0.WhenPressed(new Turn(0.0));
	turnTo45.WhenPressed(new Turn(45));
	turnTo90.WhenPressed(new Turn(90));
	turnTo135.WhenPressed(new Turn(135));
	turnTo180.WhenPressed(new Turn(180));
	turnTo225.WhenPressed(new Turn(-135));
	turnTo270.WhenPressed(new Turn(-90));
	turnTo315.WhenPressed(new Turn(-45));

	forkStow.WhenPressed(new SetForkPosition(114));
	forkUp.WhenPressed(new SetForkPosition(267));
	forkGround.WhenPressed(new SetForkPosition(478));
	/*allIn.WhenPressed(new SetManipulator(new SetArmWristPosition(RocketHeight::ALL_IN), new SetArmWristPosition(RocketHeight::ALL_IN)));
	low.WhileHeld(new SetManipulator(new SetArmWristPosition(RocketHeight::LOW), new SetArmWristPosition(RocketHeight::LOW)));
	medium.WhileHeld(new SetManipulator(new SetArmWristPosition(RocketHeight::MEDIUM), new SetArmWristPosition(RocketHeight::MEDIUM)));
	high.WhileHeld(new SetManipulator(new SetArmWristPosition(RocketHeight::HIGH), new SetArmWristPosition(RocketHeight::HIGH)));
	ship.WhileHeld(new SetManipulator(new SetArmWristPosition(RocketHeight::SHIP), new SetArmWristPosition(RocketHeight::SHIP)));*/

	allIn.WhileHeld(new SetArmWristPositionSecure(DialPosition::ALL_IN));
	pickup.WhileHeld(new SetArmWristPosition(DialPosition::PICKUP));
	low.WhileHeld(new SetArmWristPosition(DialPosition::LOW));
	ship.WhileHeld(new SetArmWristPosition(DialPosition::SHIP));
	medium.WhileHeld(new SetArmWristPosition(DialPosition::MEDIUM));
	high.WhileHeld(new SetArmWristPosition(DialPosition::HIGH));

	fodToggle.WhenPressed(new BooleanToggle(&fod, [](bool newValue) {
		
	}));
} //OI()

void OI::Update() {
	if(buttonBoard.GetRawButton(V_MODE_OVERRIDE)) {
		Robot::arm->SetVelocity(buttonBoard.GetRawAxis(-1));// The value is already [-1, 1]
		Robot::wrist->SetVelocity(buttonBoard.GetRawAxis(-1));
	} else if(buttonBoard.GetRawButton(POSITION_OVERRIDE)) {
		Robot::arm->SetSetpoint((int) mapValues(buttonBoard.GetRawAxis(ARM_AXIS), -1.0, 1.0, Robot::arm->GetArmCargoPosition(DialPosition::ALL_IN), Robot::arm->GetArmCargoPosition(DialPosition::HIGH)));
		Robot::wrist->SetSetpoint((int) mapValues(buttonBoard.GetRawAxis(WRIST_AXIS), -1.0, 1.0, Robot::arm->GetWristCargoPosition(DialPosition::ALL_IN), Robot::arm->GetWristCargoPosition(DialPosition::HIGH)));
	} else {//Normal dial control

	}
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

CargoOrHatch OI::IsCargoMode() {
	return (buttonBoard.GetRawButton(CARGO_HATCH_TOGGLE) ? CargoOrHatch::HATCH : CargoOrHatch::CARGO);
}


}//frc2019
