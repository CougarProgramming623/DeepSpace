/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "Robot.h"
#include "RobotConstants.h"

const double TPS_STRAFE = 10.0;

namespace frc2019 {
AutoDrive::AutoDrive(double distance) {
	Requires(Robot::driveTrain.get()); //requires the Drivetrain subsystem to function
	m_Distance = distance;
	m_MaxTicks = distance;
} //AutoDrive()

void AutoDrive::Initialize() {
	m_InitialTicks = Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION); // saves the inital tick count because it does not reset
	Robot::driverHasControl = false;
} //Initialize()

void AutoDrive::Execute() {
	std::stringstream ss;
	double bl = Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_VELOCITY);
	double br = Robot::driveTrain->GetDriveTalonData(DriveTalon::RIGHT_REAR, TalonData::SENSOR_VELOCITY);
	double fl = Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_FRONT, TalonData::SENSOR_VELOCITY);
	double fr = Robot::driveTrain->GetDriveTalonData(DriveTalon::RIGHT_FRONT, TalonData::SENSOR_VELOCITY);
	ss << "Wheel velocity bl " << bl << " br " << br << " fl " << fl << " fr " << fr;

	DriverStation::ReportError(ss.str());
	Robot::driveTrain->CartesianDrive(0.0, 0.4, 0.0, 0.0, true); //input power to the x parameter
} //Execute()

bool AutoDrive::IsFinished() { 
	int ticks = abs(Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION) - m_InitialTicks);
	DriverStation::ReportError("Current tick: " + std::to_string(ticks) + " target: " + std::to_string(m_MaxTicks));
	return ticks >= m_MaxTicks; //finish command if ticks driven is greater than max ticks
} //IsFinished()

void AutoDrive::End() {
	Robot::driverHasControl = true;
} //End()

void AutoDrive::Interrupted() {

} //Interrupted()
} //frc2019
