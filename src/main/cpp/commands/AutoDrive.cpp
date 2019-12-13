/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "Robot.h"
#include "RobotConstants.h"
#include "AHRS.h"

const double TPS_STRAFE = 10.0;

namespace frc2019 {
AutoDrive::AutoDrive(double distance) : frc::Command("AutoDrive") { // , frc::PIDOutput() 
	Requires(Robot::driveTrain.get()); //requires the Drivetrain subsystem to function
	m_Distance = distance;
	m_MaxTicks = 40 * distance;

	
	
} //AutoDrive()

void AutoDrive::Initialize() {
	frc::DriverStation::ReportError(std::to_string(reinterpret_cast<size_t>(Robot::navx.get())));
	frc::DriverStation::ReportError(std::to_string(Robot::navx.get()->GetYaw()));

	//m_angle = Robot::navx->GetYaw();

	m_InitialTicks = Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION); // saves the inital tick count because it does not reset
	Robot::driverHasControl = false;


	/*
	turnController = new PIDController(0.051, 0.0, 0.022, Robot::navx.get(), this); //initializes a PIDController with a kP, kI, kD, PIDSource, and PIDOuput
	turnController->SetInputRange(-180.0f, 180.0f); //sets input range to an angle
	turnController->SetOutputRange(-1.0, 1.0); //sets output range to a motor power
	turnController->SetAbsoluteTolerance(2.0f); //makes it so the robot ends at most 2 degrees of its target angle
	turnController->SetSetpoint(m_angle); //sets target angle
	turnController->SetContinuous(true);
	turnController->Enable();
	*/
	
} //Initialize()

void AutoDrive::Execute() {
	//Robot::driveTrain->CartesianDrive(0, 0, .2, Robot::navx.get()->GetYaw(), false);
	//turnController->SetSetpoint(m_angle);
	std::stringstream ss;
	double bl = Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_VELOCITY);
	double br = Robot::driveTrain->GetDriveTalonData(DriveTalon::RIGHT_REAR, TalonData::SENSOR_VELOCITY);
	double fl = Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_FRONT, TalonData::SENSOR_VELOCITY);
	double fr = Robot::driveTrain->GetDriveTalonData(DriveTalon::RIGHT_FRONT, TalonData::SENSOR_VELOCITY);
	ss << "Wheel velocity bl " << bl << " br " << br << " fl " << fl << " fr " << fr;
	
	frc::DriverStation::ReportError("Current angle: " + std::to_string(Robot::navx->GetYaw()));

	DriverStation::ReportError(ss.str());
	Robot::driveTrain->CartesianDrive(0.0, 0.2, 0.0, 0.0, true); //input power to the x parameter
} //Execute()

bool AutoDrive::IsFinished() { 
	//frc::DriverStation::ReportError("Current angle: " + std::to_string(Robot::navx->GetYaw()));

	int ticks = abs(Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION) - m_InitialTicks);
	DriverStation::ReportError("Current tick: " + std::to_string(ticks) + " target: " + std::to_string(m_MaxTicks));
	
	return ticks >= m_MaxTicks; //finish command if ticks driven is greater than max ticks
} //IsFinished()

void AutoDrive::End() {
	Robot::driverHasControl = true;
} //End()

void AutoDrive::Interrupted() {

} //Interrupted()
/*
void AutoDrive::PIDWrite(double output)
{
	rotateToAngleRate = output; //sets rotateToAngleRate to output from the PID loop running in the background
} //PIDWrite()
*/
} //frc2019
