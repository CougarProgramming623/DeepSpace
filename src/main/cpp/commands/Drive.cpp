
#include "commands/Drive.h"
#include "Robot.h"
#include "OI.h"
#include "Constants.h"
#include "RobotConstants.h"

namespace frc2019 {

Drive::Drive() {
	Requires(Robot::driveTrain.get()); //dependent on the Drivetrain Subsystem
} //Drive()

void Drive::Initialize() {
	
} //Initialize()

void Drive::Execute() {
	using namespace ohs623;
	//get the x, y, and z values from the joystick
	double y = -OI::driverJoystick.GetY(); 
	double x = OI::driverJoystick.GetX();
	double rot = OI::driverJoystick.GetZ();
	double gyro = Robot::navx->GetYaw();

	//apply a 0.075 deadband on the x and y axes
	y = abs(y) <= 0.075f ? 0 : y;
	x = abs(x) <= 0.075f ? 0 : x;
	rot = abs(rot) <= 0.05f ? 0 : rot; //0.05 deadband on the z axis
	if (Robot::driverHasControl) {
		if (Robot::oi->IsFOD()) {
			//Robot::driveTrain->FODDrive(y, x, rot, gyro);
			Robot::driveTrain->CartesianDrive(y, x, rot/2, gyro, !Robot::oi->IsPercentOutputMode()); //field oriented drive
		} else {// Is alignment
			// Disabled for now - dims down the effect of x and rot
			//x = ReduceValue(x, 3.0);
			//rot = ReduceValue(rot, 2.0);
			//Robot::driveTrain->FODDrive(y, x, rot, 0.0);
			Robot::driveTrain->CartesianDrive(y, x, rot/2, 0.0, !Robot::oi->IsPercentOutputMode()); //robot oriented drive
		}
	}
} //Execute()

bool Drive::IsFinished() { 
	return false;
} //IsFinished()

void Drive::End() {

} //End()

void Drive::Interrupted() {

} //Interrupted()
}//frc2019
