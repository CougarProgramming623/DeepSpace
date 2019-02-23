/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "Robot.h"
#include "RobotConstants.h"

namespace frc2019 {
AutoDrive::AutoDrive(double distance, bool strafe) {
	Requires(Robot::driveTrain.get()); //requires the Drivetrain subsystem to function
	initialTicks = abs(Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION)); // saves the inital tick count because it does not reset
	m_distance = distance;
	isStrafing = strafe;
	maxTicks = m_distance * (strafe ? S_TICKS_PER_INCH : TICKS_PER_INCH);
} //AutoDrive()

void AutoDrive::Initialize() {
	
} //Initialize()

void AutoDrive::Execute() {
	if (isStrafing) {
		Robot::driveTrain->CartesianDrive(0.0, 0.5, 0.0, Robot::navx->GetYaw()); //input power to the x parameter
	}
	else {
		Robot::driveTrain->CartesianDrive(0.5, 0.0, 0.0, Robot::navx->GetYaw()); //input power to the y parameter
	}
} //Execute()

bool AutoDrive::IsFinished() { 
	int ticks = abs(Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION) - initialTicks);
	return ticks >= maxTicks; //finish command if ticks driven is greater than max ticks
} //IsFinished()

void AutoDrive::End() {
} //End()

void AutoDrive::Interrupted() {

} //Interrupted()
} //frc2019