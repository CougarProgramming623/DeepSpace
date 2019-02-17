
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

	if(abs(y) <= 0.05f) {
		y = 0;
	}
	if(abs(x) <= 0.05f) {
		x = 0;
	}
	if(abs(rot) <= 0.05f) {
		rot = 0;
	}
	/*
	y *= kMAX_VELOCITY;
	x *= kMAX_VELOCITY;
	rot *= kMAX_VELOCITY;
	*/
	double gyro = Robot::navx->GetYaw();

	SmartDashboard::PutNumber("angle", gyro);

	if (Robot::oi->IsFOD()) {
		//Robot::driveTrain->FODDrive(y, x, rot, gyro);
		Robot::driveTrain->CartesianDrive(y, x, rot/2, gyro);
	} else {// Is alignment
		// Disabled for now - dims down the effect of x and rot
		//x = ReduceValue(x, 3.0);
		//rot = ReduceValue(rot, 2.0);
		//Robot::driveTrain->FODDrive(y, x, rot, 0.0);
		Robot::driveTrain->CartesianDrive(y, x, rot/2, 0.0);
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
