/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetForkPosition.h"
#include "Robot.h"

namespace frc2019 {

SetForkPosition::SetForkPosition(int setpoint) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::fork.get());
  m_setpoint = setpoint;
} //SetForkPosition()

// Called just before this Command runs the first time
void SetForkPosition::Initialize() {
    DriverStation::ReportError("setting fork: " + std::to_string(m_setpoint));
} //Initialize()

// Called repeatedly when this Command is scheduled to run
void SetForkPosition::Execute() {
  Robot::fork->SetSetpoint(m_setpoint); //set setpoint of fork subsystem
  /*
  if(Robot::oi->UsingForkSlider()) {
    double slider = OI::buttonBoard.GetRawAxis(1);
    m_setpoint = mapValues(slider, -1, +1, 0, 313);
  }
  */
  frc::SmartDashboard::PutNumber("fork position", Robot::fork->GetForkTalonData(TalonData::SENSOR_POSITION));
  frc::SmartDashboard::PutNumber("fork error", Robot::fork->GetForkTalonData(TalonData::ERROR));
} //Execute()

// Make this return true when this Command no longer needs to run execute()
bool SetForkPosition::IsFinished() { 
  return true; 
} //IsFinished()

// Called once after isFinished returns true
void SetForkPosition::End() {

} //End()

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetForkPosition::Interrupted() {

} //Interrupted
} //frc2019