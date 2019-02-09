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
	Requires(Robot::driveTrain.get()); //dependent on the Drivetrain subsystem
	initialTicks = abs(Robot::driveTrain->GetTicks()); //get current ticks reading since encoders do not reset
	m_distance = distance;
	isStrafing = strafe;
	maxTicks = m_distance * (isStrafing ? S_TICKS_PER_INCH : TICKS_PER_INCH);
}

void AutoDrive::Initialize() {
}

void AutoDrive::Execute() {
	if (isStrafing) {
		Robot::driveTrain->FODDrive(0.0, 0.5, 0.0, Robot::navx->GetYaw()); //input power to xSpeed if we are strafing
	}
	else {
		Robot::driveTrain->FODDrive(0.5, 0.0, 0.0, Robot::navx->GetYaw()); //input power to ySpeed if we are not strafing
	}
	
	ticksDriven = Robot::driveTrain->GetTicks() - initialTicks; //ticksDriven = current amount of ticks minus initial reading
	DriverStation::ReportError("Ticks Driven: " + std::to_string(ticksDriven)); //report to driverstation the number of ticks driven
}

bool AutoDrive::IsFinished() { 
	return ticksDriven >= maxTicks; //check to see if ticksDriven has surpassed the amount ticks needed to be driven, if so end the command
 }

void AutoDrive::End() {
}

void AutoDrive::Interrupted() {}
}