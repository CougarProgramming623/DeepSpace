
#include "commands/Drive.h"
#include "Robot.h"
#include "OI.h"
#include "Constants.h"

using namespace ohs623;

namespace frc2019 {

Drive::Drive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void Drive::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
	double y = -OI::driverJoystick.GetY();
	double x = -OI::driverJoystick.GetX();
	double rot = OI::driverJoystick.GetZ();
	double gyro = Robot::navx->GetYaw();
	if (Robot::oi->IsFOD()) {
		Robot::driveTrain->FODDrive(y, x, rot, gyro);
		DriverStation::ReportError("FOD Drive!");
	} else {// Is alignment
		// Disabled for now - dims down the effect of x and rot
		//x = ReduceValue(x, 3.0);
		//rot = ReduceValue(rot, 2.0);
		Robot::driveTrain->FODDrive(y, x, rot, 0.0);
		DriverStation::ReportError("Robot Drive!");

	}
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