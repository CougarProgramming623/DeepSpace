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
  pastPosition = 0;
  Robot::vacuum->SetServoPosition(0);
}

// Called just before this Command runs the first time
void SetServo::Initialize() {
    Robot::vacuum->SetServoPosition(m_position);
}

// Called repeatedly when this Command is scheduled to run
void SetServo::Execute() {
  /*
  DriverStation::ReportError("Servo Position: " + std::to_string(Robot::vacuum->GetServoPosition()));
  DriverStation::ReportError("Servo Target: " + std::to_string(m_position));
  
  if(Robot::vacuum->GetServoPosition() < m_position) {
    Robot::vacuum->SetServoPosition(Robot::vacuum->GetServoPosition() + 0.1);
    DriverStation::ReportError("incrementing");
  }
  
  if(Robot::vacuum->GetServoPosition() > m_position) {
    Robot::vacuum->SetServoPosition(Robot::vacuum->GetServoPosition() - 0.1);
    DriverStation::ReportError("decrementing");
  }
  */
}

// Make this return true when this Command no longer needs to run execute()
bool SetServo::IsFinished() { 
  //return (Robot::vacuum->GetServoPosition() == m_position); 
  return true;
}

// Called once after isFinished returns true
void SetServo::End() {
  DriverStation::ReportError("Finished servo set");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetServo::Interrupted() {}
}