
#include "commands/Drive.h"
#include "Robot.h"
#include "OI.h"
#include "Constants.h"


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
	
	//get the angle reading fromt the gyro
	double angle = Robot::navx->GetYaw();
	if (Robot::oi->IsFOD()) {
		Robot::driveTrain->FODDrive(y, x, rot, angle); //used when we are in Field Oriented Driving Mode
	} else {// Is alignment
		// Disabled for now - dims down the effect of x and rot
		//x = ReduceValue(x, 3.0);
		//rot = ReduceValue(rot, 2.0);
		Robot::driveTrain->FODDrive(y, x, rot, 0.0); //used when we are in Robot Oriented Drivng Mode
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
