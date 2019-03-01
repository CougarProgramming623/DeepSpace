/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetServo.h"
#include "Robot.h"

namespace frc2019 {
SetServo::SetServo(double pos) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::vacuum.get());
  m_position = pos;
}

// Called just before this Command runs the first time
void SetServo::Initialize() {
  Robot::vacuum->SetServoPosition(m_position);
}

// Called repeatedly when this Command is scheduled to run
void SetServo::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetServo::IsFinished() { return true; }

// Called once after isFinished returns true
void SetServo::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetServo::Interrupted() {}
}