/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ModeSwitch.h"
#include "Cob.h"
#include "CobConstants.h"

namespace frc2019 {

ModeSwitch::ModeSwitch(bool* pointer, bool mode) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  boolean = pointer;
  state = mode;
}

// Called just before this Command runs the first time
void ModeSwitch::Initialize() {
  *boolean = state;
  Cob::PushValue(COB_HATCH, state);
}

// Called repeatedly when this Command is scheduled to run
void ModeSwitch::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ModeSwitch::IsFinished() { return true; }

// Called once after isFinished returns true
void ModeSwitch::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ModeSwitch::Interrupted() {}
}