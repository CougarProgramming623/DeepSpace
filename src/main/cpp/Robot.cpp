
#include "Robot.h"
#include "Cob.h"
#include <frc/DriverStation.h>
namespace frc2019 {

	std::shared_ptr<DriveTrain> Robot::driveTrain;
	std::shared_ptr<AHRS> Robot::navx;
	std::shared_ptr<OI> Robot::oi;
	
	void Robot::RobotInit() {
		Cob::InitBoard();
		driveTrain.reset(new DriveTrain());
		oi.reset(new OI());
		try {
			navx.reset(new AHRS(SPI::Port::kMXP));
		} catch (std::exception &ex) {
			std::string err = "Error instantiating navX MXP: ";
			err += ex.what();
			DriverStation::ReportError(err.c_str());
		}
		
		navx->ZeroYaw();

		//CameraServer::GetInstance()->StartAutomaticCapture();
	}
		
	void Robot::AutonomousInit() {

	}

	void Robot::AutonomousPeriodic() {
		frc::Scheduler::GetInstance()->Run();
	}

	void Robot::TeleopInit() {

	}

void Robot::TeleopPeriodic() {
	DriverStation::ReportError("TeleopPeriodic");
	frc::Scheduler::GetInstance()->Run();
	Cob::PushRotation(navx->GetYaw());
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



