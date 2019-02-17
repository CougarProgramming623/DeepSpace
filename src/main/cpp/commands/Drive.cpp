
#include "commands/Drive.h"
#include "Robot.h"
#include "OI.h"
#include "Constants.h"
#include "RobotConstants.h"


namespace frc2019 {

Drive::Drive() {
	Requires(Robot::driveTrain.get()); //dependent on the Drivetrain Subsystem
}

void Drive::Initialize() {
	
}

void Drive::Execute() {
	using namespace ohs623;
	//get the x, y, and z values from the joystick
	double y = -OI::driverJoystick.GetY(); 
	double x = OI::driverJoystick.GetX();
	double rot = OI::driverJoystick.GetZ();

	y *= kMAX_VELOCITY;
	x *= kMAX_VELOCITY;
	rot *= kMAX_VELOCITY;
	double gyro = Robot::navx->GetYaw();

	if (Robot::oi->IsFOD()) {
		//Robot::driveTrain->FODDrive(y, x, rot, gyro);
		Robot::driveTrain->CartesianDrive(y, x, rot, gyro);
	} else {// Is alignment
		// Disabled for now - dims down the effect of x and rot
		//x = ReduceValue(x, 3.0);
		//rot = ReduceValue(rot, 2.0);
		//Robot::driveTrain->FODDrive(y, x, rot, 0.0);
		Robot::driveTrain->CartesianDrive(y, x, rot, 0.0);
	}
}

bool Drive::IsFinished() { 
	return false;
}

void Drive::End() {

}

void Drive::Interrupted() {

}
}//frc2019
