#include "Robot.h"
#include "Cob.h"
#include <frc/DriverStation.h>
#include "commands/Turn.h"


namespace frc2019 {

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<AHRS> Robot::navx;
std::shared_ptr<OI> Robot::oi(nullptr);
std::shared_ptr<Arm> Robot::arm;
std::shared_ptr<Vacuum> Robot::vacuum;
std::shared_ptr<Wrist> Robot::wrist;
std::shared_ptr<Climb> Robot::climb;

void Robot::RobotInit() {
	Cob::InitBoard();
	driveTrain.reset(new DriveTrain());
	arm.reset(new Arm());
	wrist.reset(new Wrist());
	vacuum.reset(new Vacuum());
	oi.reset(new OI());
	climb.reset(new Climb());
	try {
		navx.reset(new AHRS(SPI::Port::kMXP)); //instantiates the gyro
	} catch (std::exception &ex) {
		std::string err = "Error instantiating navX MXP: ";
		err += ex.what();
		DriverStation::ReportError(err.c_str());
	}
  
	navx->ZeroYaw(); //makes it so whatever start position the robot is facing is 0 degrees
	std::string color = frc::DriverStation::GetInstance().GetAlliance() == frc::DriverStation::Alliance::kRed ? "red" : "blue"; //determine alliance color as a string
	Cob::PushValue(COB_ALLIANCE_COLOR, color); //push the alliance color as a string
	Cob::PushValue(COB_SHUTDOWN_BEAGLEBONE, false);
	Cob::PushValue(COB_ENDGAME, false);
	DriverStation::ReportError("Finished RobotInit()");
} //RobotInit()

void Robot::RobotPeriodic() {
	//pushed during robot periodic because these values constantly change
	Cob::PushValue(COB_TIME, DriverStation::GetInstance().GetMatchTime());
	Cob::PushValue(COB_X_VEL,Robot::navx->GetVelocityX());
	Cob::PushValue(COB_Y_VEL,Robot::navx->GetVelocityY());
	Cob::PushValue(COB_ROTATION,Robot::navx->GetYaw());

	Cob::PushValue(COB_MAIN_ARM_ROTATION, arm->GetArmTalonData(TalonData::SENSOR_POSITION));
	Cob::PushValue(COB_WRIST_ROTATION, wrist->GetWristTalonData(TalonData::SENSOR_POSITION));


	if(Cob::GetValue<bool>(COB_PULL_ARM_SETPOINTS)) {
		arm->PullSetpoints();
		Cob::PushValue(COB_PULL_ARM_SETPOINTS, false);
	}

	if(Cob::GetValue<bool>(COB_SAVE_ARM_SETPOINTS)) {
		arm->SaveSetpoints();
		Cob::PushValue(COB_SAVE_ARM_SETPOINTS, false);
	}

	//Cob::PushValue(COB_MAIN_ARM_ROTATION,Robot::arm->GetPotData());
	//vacuum->SetServoPosition(1.0);
	oi->Update();
	vacuum->Update();
}

void Robot::AutonomousInit() {
	navx->ZeroYaw();
	//autonomousCommand.reset(new Turn(90.0f)); //set the autonomous command or command group here 
	/*
	if(autonomousCommand)
		autonomousCommand->Start();
		*/
	Cob::PushValue(COB_ENDGAME, false);
} //AutonomousInit()

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
} //AutonomousPeriodic()

void Robot::TeleopInit() {
	isTeleop = true && DriverStation::GetInstance().GetMatchTime() > -1.0;
	navx->ZeroYaw();
} //TeleopInit()

void Robot::TeleopPeriodic() {
	double time = DriverStation::GetInstance().GetMatchTime();
	if(time >= 0.0 && time <= 30)
		Cob::PushValue(COB_ENDGAME, true);
	frc::Scheduler::GetInstance()->Run();
} //TeleopPeriodic

void Robot::DisabledInit() {
	if(isTeleop) {
		Cob::PushValue(COB_SHUTDOWN_BEAGLEBONE, true);
		isTeleop = false;
	}
}

void Robot::TestInit() {
	arm->SetVelocity(0.0f);
	wrist->SetVelocity(0.0f);
} //TestInit()

void Robot::TestPeriodic() {
	DriverStation::ReportError(std::to_string(vacuum->GetCurrent()));
} //TestPeriodic()
} //frc2019

#ifndef RUNNING_FRC_TESTS
int main() { 
	using namespace frc2019;
	return frc::StartRobot<Robot>();
} //main()
#endif
