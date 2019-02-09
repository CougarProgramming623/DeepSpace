#include "Robot.h"
#include "Cob.h"
#include <frc/DriverStation.h>
#include "commands/PositveAngleTurnTest.h"

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
	DriverStation::ReportError("constructed arm");
	oi.reset(new OI());
	DriverStation::ReportError("constructed oi");
	try {
		navx.reset(new AHRS(SPI::Port::kMXP));
		DriverStation::ReportError("constructed navx");
	} catch (std::exception &ex) {
		std::string err = "Error instantiating navX MXP: ";
		err += ex.what();
		DriverStation::ReportError(err.c_str());
	}
  
	Robot::navx.get()->ZeroYaw();
	std::string color = frc::DriverStation::GetInstance().GetAlliance() == frc::DriverStation::Alliance::kRed ? "red" : "blue";
	Cob::PushValue(COB_ALLIANCE_COLOR, color);
}

void Robot::RobotPeriodic() {
	Cob::PushValue(COB_X_VEL,Robot::navx->GetVelocityX());
	Cob::PushValue(COB_Y_VEL,Robot::navx->GetVelocityY());
	Cob::PushValue(COB_ROTATION,Robot::navx->GetYaw());
	Cob::PushValue(COB_MAIN_ARM_ROTATION,Robot::arm->GetPotData());
}
		
void Robot::AutonomousInit() {
	navx->ZeroYaw();
	autonomousCommand.reset(new PositveAngleTurnTest());
	if(autonomousCommand)
		autonomousCommand->Start();
	//CameraServer::GetInstance()->StartAutomaticCapture();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	//DriverStation::ReportError("TeleopPeriodic");
	DriverStation::ReportError(std::to_string(arm->GetPotData()));
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestInit() {
}

void Robot::TestPeriodic() {
}
} //frc2019

#ifndef RUNNING_FRC_TESTS
int main() { 
	using namespace frc2019;
	return frc::StartRobot<Robot>();
}
#endif
