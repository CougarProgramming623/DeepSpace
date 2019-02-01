
#include "Robot.h"
#include "COB/CougarOpticBoard.h"
#include <frc/DriverStation.h>
#include <WPILib.h>

namespace frc2019 {

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
	CougarOpticBoard::PushRotation(navx->GetYaw());
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