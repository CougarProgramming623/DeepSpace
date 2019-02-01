
#include "commands/Drive.h"
#include "Robot.h"
#include "ControlConstants.h"

namespace frc2019 {

Drive::Drive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
	joystick.reset(new Joystick(DRIVER_JOYSTICK));
}

// Called just before this Command runs the first time
void Drive::Initialize() {
	y = x = rot = angle = 0;
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
	y = -joystick->GetY();
	x = -joystick->GetX();
	rot = joystick->GetZ();
	angle = Robot::navx->GetYaw();
	Robot::driveTrain->fodDrive(y, x, rot, angle);
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() { 
	return false;
}

// Called once after isFinished returns true
void Drive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {}


}//frc2019