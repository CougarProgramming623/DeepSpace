/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnOnVacuum.h"
#include "Robot.h"

namespace frc2019 {
TurnOnVacuum::TurnOnVacuum() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::vacuum.get());
}

// Called just before this Command runs the first time
void TurnOnVacuum::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurnOnVacuum::Execute() {
  Robot::vacuum->Suck();
}

// Make this return true when this Command no longer needs to run execute()
bool TurnOnVacuum::IsFinished() { return false; }

// Called once after isFinished returns true
void TurnOnVacuum::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnOnVacuum::Interrupted() {}
}