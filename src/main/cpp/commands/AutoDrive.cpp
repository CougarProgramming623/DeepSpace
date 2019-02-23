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
	currentTicks = abs(Robot::driveTrain->GetTicks()); // saves the inital tick count because it does not reset
	m_distance = distance;
	isStrafing = strafe;
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
	double maxTicks;
	if (isStrafing){
		maxTicks = m_distance * S_TICKS_PER_INCH;
	}
	else {
		maxTicks = m_distance * TICKS_PER_INCH;
	}
	int ticks = abs(Robot::driveTrain->GetTicks() - currentTicks);
	return maxTicks <= ticks;
 }

void AutoDrive::End() {
}

void AutoDrive::Interrupted() {}
}