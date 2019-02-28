/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ReadDIO.h"
#include <frc/WPILib.h>
#include "Robot.h"
#include "Cob.h"

namespace frc2019 {
ReadDIO::ReadDIO() : dioInput(0) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ReadDIO::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ReadDIO::Execute() {
  DriverStation::ReportError(std::to_string(dioInput.Get()));
  Cob::PushValue(COB_HATCH_PRESSED, dioInput.Get());//return boolean (force sensor triggered)
}

// Make this return true when this Command no longer needs to run execute()
bool ReadDIO::IsFinished() { return false; }

// Called once after isFinished returns true
void ReadDIO::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReadDIO::Interrupted() {}
}
