/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "Robot.h"
#define TICKS_PER_INCH 19.33570146
#define S_TICKS_PER_INCH 27.83584539


AutoDrive::AutoDrive(double distance, bool strafe) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::driveTrain.get());
  currentTicks = abs(Robot::driveTrain->getTicks());
  m_distance = distance;
  isStraffing = strafe;
}

// Called just before this Command runs the first time
void AutoDrive::Initialize() {
  //SetTimeout(3);
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
  if (isStraffing){
    Robot::driveTrain->fodDrive(0.0, 0.5, 0.0, Robot::navx->GetYaw());
    DriverStation::ReportError("Ticks Driven: " + std::to_string(Robot::driveTrain->getTicks()-currentTicks));
  }
  else {
    Robot::driveTrain->fodDrive(0.5, 0.0, 0.0, Robot::navx->GetYaw());
    DriverStation::ReportError("Ticks Driven: " + std::to_string(Robot::driveTrain->getTicks()-currentTicks));
  }
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrive::IsFinished() { 
  double maxTicks;
  if (isStraffing){
    maxTicks = m_distance * S_TICKS_PER_INCH;
  }
  else {
    maxTicks = m_distance * TICKS_PER_INCH;
  }
  int ticks = abs(Robot::driveTrain->getTicks() - currentTicks);
  return maxTicks <= ticks;
 }

// Called once after isFinished returns true
void AutoDrive::End() {
  //Robot::driveTrain->fodDrive(0.0, 0.0, 0.0, Robot::navx->GetYaw());
  int ticksDriven = Robot::driveTrain->getTicks() - currentTicks;
  DriverStation::ReportError("Ticks Driven: " + std::to_string(ticksDriven));
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {}
