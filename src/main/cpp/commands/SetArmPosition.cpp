/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetArmPosition.h"
#include "Robot.h"

namespace frc2019 {
SetArmPosition::SetArmPosition(int setpoint) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::arm.get());
  m_setpoint = setpoint;
}

// Called just before this Command runs the first time
void SetArmPosition::Initialize() {
  SetTimeout(10);
} 

// Called repeatedly when this Command is scheduled to run
void SetArmPosition::Execute() {
  DriverStation::ReportError("Executing arm command");
  Robot::arm->SetSetpoint(m_setpoint);
}

// Make this return true when this Command no longer needs to run execute()
bool SetArmPosition::IsFinished() { 
  return IsTimedOut();
}

// Called once after isFinished returns true
void SetArmPosition::End() {
    //Robot::arm->SetSetpoint(Robot::arm->GetPositionData());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetArmPosition::Interrupted() {}
}