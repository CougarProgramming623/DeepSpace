
#include "commands/Drive.h"
#include "Robot.h"


namespace frc2019 {

Drive::Drive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void Drive::Initialize() {
	y = x = rot = angle = 0;
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
	y = -Robot::oi->GetDriverJoystick()->GetY();
	x = -Robot::oi->GetDriverJoystick()->GetX();
	rot = Robot::oi->GetDriverJoystick()->GetZ();
	angle = Robot::navx->GetYaw();
	Robot::driveTrain->FODDrive(y, x, rot, angle);
	//frc::DriverStation::ReportError("Ticks: " + std::to_string(Robot::driveTrain->GetTicks()));
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