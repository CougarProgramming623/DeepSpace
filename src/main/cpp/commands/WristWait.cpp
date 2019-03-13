/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WristWait.h"

#include "frc/DriverStation.h"
#include "Robot.h"

namespace frc2019 {

WristWait::WristWait() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	
}

// Called just before this Command runs the first time
void WristWait::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WristWait::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool WristWait::IsFinished() { 
	int error = abs(Robot::wrist->GetWristPosition() - Robot::arm->GetArmPosition(DialPosition::ALL_IN, CargoOrHatch::CARGO));
	frc::DriverStation::ReportError("Offset: " + std::to_string(Robot::arm->GetWristOffset()) + "Setpoint: " + std::to_string(Robot::arm->GetArmPosition(DialPosition::ALL_IN, CargoOrHatch::CARGO)));
	frc::DriverStation::ReportError("Wrist pos: " + std::to_string(Robot::wrist->GetWristPosition()) + ", error " + std::to_string(error));
	return error < 30;
}

// Called once after isFinished returns true
void WristWait::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WristWait::Interrupted() {}


}