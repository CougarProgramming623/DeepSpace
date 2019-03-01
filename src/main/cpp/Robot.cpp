#include "Robot.h"
#include "Cob.h"
#include <frc/DriverStation.h>
#include "commands/Turn.h"


namespace frc2019 {

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<AHRS> Robot::navx;
std::shared_ptr<OI> Robot::oi;
std::shared_ptr<Arm> Robot::arm;
std::shared_ptr<Vacuum> Robot::vacuum;
std::shared_ptr<HatchPickup> Robot::fork;
std::shared_ptr<Wrist> Robot::wrist;
std::shared_ptr<Climb> Robot::climb;

void Robot::RobotInit() {
	Cob::InitBoard();
	driveTrain.reset(new DriveTrain());
	DriverStation::ReportError("constructed drivetrain");
	arm.reset(new Arm());
	wrist.reset(new Wrist());
	vacuum.reset(new Vacuum());
	oi.reset(new OI());
	fork.reset(new HatchPickup());
	climb.reset(new Climb());
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
} //RobotInit()

void Robot::RobotPeriodic() {
	//pushed during robot periodic because these values constantly change
	Cob::PushValue(COB_X_VEL,Robot::navx->GetVelocityX());
	Cob::PushValue(COB_Y_VEL,Robot::navx->GetVelocityY());
	Cob::PushValue(COB_ROTATION,Robot::navx->GetYaw());
	Cob::PushValue(COB_MAIN_ARM_ROTATION, arm->GetArmTalonData(TalonData::SENSOR_POSITION));
	Cob::PushValue(COB_WRIST_ROTATION, wrist->GetWristTalonData(TalonData::SENSOR_POSITION));

	//Cob::PushValue(COB_MAIN_ARM_ROTATION,Robot::arm->GetPotData());
}

void Robot::AutonomousInit() {
	navx->ZeroYaw();
	autonomousCommand.reset(new Turn(90.0f)); //set the autonomous command or command group here
	if(autonomousCommand)
		autonomousCommand->Start();
} //AutonomousInit()

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
} //AutonomousPeriodic()

void Robot::TeleopInit() {

} //TeleopInit()

void Robot::TeleopPeriodic() {
	frc::SmartDashboard::PutNumber("LF Velocity", driveTrain->GetDriveTalonData(DriveTalon::LEFT_FRONT, TalonData::SENSOR_VELOCITY));
	frc::SmartDashboard::PutNumber("LR Velocity", driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_VELOCITY));
	frc::SmartDashboard::PutNumber("RF Velocity", driveTrain->GetDriveTalonData(DriveTalon::RIGHT_FRONT, TalonData::SENSOR_VELOCITY));
	frc::SmartDashboard::PutNumber("RR Velocity", driveTrain->GetDriveTalonData(DriveTalon::RIGHT_REAR, TalonData::SENSOR_VELOCITY));
	frc::Scheduler::GetInstance()->Run();
} //TeleopPeriodic

void Robot::TestInit() {

} //TestInit()

void Robot::TestPeriodic() {

} //TestPeriodic()
} //frc2019

#ifndef RUNNING_FRC_TESTS
int main() { 
	using namespace frc2019;
	return frc::StartRobot<Robot>();
} //main()
#endif
