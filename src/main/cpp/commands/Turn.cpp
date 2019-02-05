/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Turn.h"
#include "Robot.h"
#include "AHRS.h"

Turn::Turn(double angle) : frc::Command("Turn") , frc::PIDOutput() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::driveTrain.get());
  turnController = new PIDController(0.05f, 0.0f, 0.045f, Robot::navx, this);
  rotateToAngleRate = 0.0;
  m_angle = angle;
  SetTimeout(2);
}

// Called just before this Command runs the first time
void Turn::Initialize() {
  //sRobot::navx->ZeroYaw();
  turnController->SetInputRange(-180.0f, 180.0f);
  turnController->SetOutputRange(-1.0, 1.0);
  turnController->SetAbsoluteTolerance(2.0f);
  turnController->SetSetpoint(m_angle);
  turnController->SetContinuous(true);
  turnController->Enable();

}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
  frc::DriverStation::ReportError("Executing turn");
  Robot::driveTrain->fodDrive(0, 0, rotateToAngleRate / 2, Robot::navx->GetYaw());
  //if(Robot::navx->GetYaw() >= 90)
    SmartDashboard::PutNumber("Error", m_angle - Robot::navx->GetYaw());
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() { 
  return IsTimedOut();
}

// Called once after isFinished returns true
void Turn::End() {
  Robot::driveTrain->fodDrive(0,0,0,0);
  DriverStation::ReportError("Finished turn");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {}

void Turn::PIDWrite(double output)
{
  rotateToAngleRate = output;
}
