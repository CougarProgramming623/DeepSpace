/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetArmPosition.h"
#include "Robot.h"
#include "RobotConstants.h"

namespace frc2019 {
SetArmPosition::SetArmPosition(int setpoint) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::arm.get());
  m_setpoint = setpoint;
}

// Called just before this Command runs the first time
void SetArmPosition::Initialize() {
  DriverStation::ReportError("Arm going to: " + std::to_string(m_setpoint));
  if(Robot::arm->GetArmTalonData(TalonData::SENSOR_POSITION) < m_setpoint) {
    Robot::arm->SetP(UP_kP_ARM);
  } else {
    Robot::arm->SetP(DOWN_kP_ARM);
  }
  Robot::arm->SetSetpoint(m_setpoint); //set setpoint of arm subsystem
}

// Called repeatedly when this Command is scheduled to run
void SetArmPosition::Execute() {
  /*
  if(Robot::oi->UsingArmSlider()) {
    double slider = OI::buttonBoard.GetRawAxis(0);
    m_setpoint = mapValues(slider, -1, +1, 0, 449);
  } */
  frc::SmartDashboard::PutNumber("arm position", Robot::arm->GetArmTalonData(TalonData::SENSOR_POSITION));
  frc::SmartDashboard::PutNumber("arm error", Robot::arm->GetArmTalonData(TalonData::ERROR));
}

// Make this return true when this Command no longer needs to run execute()
bool SetArmPosition::IsFinished() { return true; }

// Called once after isFinished returns true
void SetArmPosition::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetArmPosition::Interrupted() {}
}
