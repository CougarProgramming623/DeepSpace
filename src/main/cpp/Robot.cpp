/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/DriverStation.h>

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<AHRS> Robot::navx;
void Robot::RobotInit() {
	driveTrain.reset(new DriveTrain());
	try {
		navx.reset(new AHRS(SPI::Port::kMXP));
		navx->ZeroYaw();
	} catch (std::exception &ex) {
		std::string err = "Error instantiating navX MXP: ";
		err += ex.what();
		DriverStation::ReportError(err.c_str());
	}
}

void Robot::AutonomousInit() {

}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
	DriverStation::ReportError("TeleopPeriodic");
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestInit() {

}

void Robot::TestPeriodic() {

}

#ifndef RUNNING_FRC_TESTS
int main() {
	return frc::StartRobot<Robot>();
}
#endif
