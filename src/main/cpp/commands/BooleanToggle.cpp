/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BooleanToggle.h"

namespace frc2019 {
BooleanToggle::BooleanToggle(bool* ptr) : boolean(ptr) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void BooleanToggle::Initialize() {
	frc::DriverStation::ReportError(std::string("Before: ") + (*boolean ? "True" : "False"));
	if(*boolean) {
		*boolean = false;
	} else {
		*boolean = true;
	}
	frc::DriverStation::ReportError(std::string("After: ") + (*boolean ? "True" : "False"));
}

// Called repeatedly when this Command is scheduled to run
void BooleanToggle::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool BooleanToggle::IsFinished() { return true; }

// Called once after isFinished returns true
void BooleanToggle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BooleanToggle::Interrupted() {}
}