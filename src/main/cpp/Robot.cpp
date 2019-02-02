
#include "Robot.h"
#include <frc/DriverStation.h>
#include <WPILib.h>

namespace frc2019 {

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<AHRS> Robot::navx;
std::shared_ptr<OI> Robot::oi;
void Robot::RobotInit() {
oi.reset(new OI());

	driveTrain.reset(new DriveTrain());
	try {
		navx.reset(new AHRS(SPI::Port::kMXP));
		navx->ZeroYaw();
	} catch (std::exception &ex) {
		std::string err = "Error instantiating navX MXP: ";
		err += ex.what();
		DriverStation::ReportError(err.c_str());
	}
	

	CameraServer::GetInstance()->StartAutomaticCapture();
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


}//frc2019