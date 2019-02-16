/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PickupControl.h"

namespace frc2019 {
PickupControl::PickupControl() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::pickup.get());
}

// Called just before this Command runs the first time
void PickupControl::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PickupControl::Execute() {
  Robot::pickup->SetSpeed(1.0);
}

// Make this return true when this Command no longer needs to run execute()
bool PickupControl::IsFinished() { return false; }

// Called once after isFinished returns true
void PickupControl::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickupControl::Interrupted() {}
}