/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveToggle.h"

namespace frc2019 {
DriveToggle::DriveToggle(bool& boolean) : boolean{boolean} {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void DriveToggle::Initialize() {
  this->boolean = !boolean;
  frc::DriverStation::ReportError("Flipped the boolean!");
}

// Called repeatedly when this Command is scheduled to run
void DriveToggle::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool DriveToggle::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveToggle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToggle::Interrupted() {}
}