#include "Robot.h"
#include "Cob.h"
#include <frc/DriverStation.h>
#include "commands/PositveAngleTurnTest.h"
#include "commands/Turn.h"

namespace frc2019 {

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<AHRS> Robot::navx;
std::shared_ptr<OI> Robot::oi;
std::shared_ptr<Arm> Robot::arm;

void Robot::RobotInit() {
	Cob::InitBoard();
	driveTrain.reset(new DriveTrain());
	DriverStation::ReportError("constructed drivetrain");
	arm.reset(new Arm());
	oi.reset(new OI());
	try {
		navx.reset(new AHRS(SPI::Port::kMXP)); //instantiates the gyro
	} catch (std::exception &ex) {
		std::string err = "Error instantiating navX MXP: ";
		err += ex.what();
		DriverStation::ReportError(err.c_str());
	}
  
	Robot::navx.get()->ZeroYaw(); //makes it so whatever start position the robot is facing is 0 degrees
	std::string color = frc::DriverStation::GetInstance().GetAlliance() == frc::DriverStation::Alliance::kRed ? "red" : "blue"; //determine alliance color as a string
	Cob::PushValue(COB_ALLIANCE_COLOR, color); //push the alliance color as a string
}

void Robot::RobotPeriodic() {
	//pushed during robot periodic because these values constantly change
	Cob::PushValue(COB_X_VEL,Robot::navx->GetVelocityX());
	Cob::PushValue(COB_Y_VEL,Robot::navx->GetVelocityY());
	Cob::PushValue(COB_ROTATION,Robot::navx->GetYaw());
	//Cob::PushValue(COB_MAIN_ARM_ROTATION,Robot::arm->GetPotData());
}
		
void Robot::AutonomousInit() {
	autonomousCommand.reset(new Turn(90.0f)); //set the autonomous command or command group here
	if(autonomousCommand)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestInit() {
}

void Robot::TestPeriodic() {
	//DriverStation::ReportError("Right: " + std::to_string(Robot::vD->GetVelocity(false)));
	frc::SmartDashboard::PutNumber("X", OI::driverJoystick.GetX());
	frc::SmartDashboard::PutNumber("Y", OI::driverJoystick.GetY());
	frc::SmartDashboard::PutNumber("Rotation", OI::driverJoystick.GetZ());
}

} //frc2019

#ifndef RUNNING_FRC_TESTS
int main() { 
	using namespace frc2019;
	return frc::StartRobot<Robot>();
}
#endif
