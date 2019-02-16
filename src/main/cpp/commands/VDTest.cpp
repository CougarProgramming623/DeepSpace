/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VDTest.h"
#include "Robot.h"
#include "OI.h"
#include "RobotConstants.h"

namespace frc2019 {
VDTest::VDTest() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::vD.get());
  joystickVal = 0;
}

// Called just before this Command runs the first time
void VDTest::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void VDTest::Execute() {
  joystickVal = -OI::driverJoystick.GetY();
  frc::SmartDashboard::PutNumber("joystick", joystickVal);
  //if(abs(joystickVal) <= 0.045)
    //joystickVal = 0;
    
  double lVelocity = joystickVal * kMAX_VELOCITY_LEFT;
  double rVelocity = joystickVal * kMAX_VELOCITY_RIGHT;

  Robot::vD->VelocityDrive(lVelocity);
}

// Make this return true when this Command no longer needs to run execute()
bool VDTest::IsFinished() { return false; }

// Called once after isFinished returns true
void VDTest::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VDTest::Interrupted() {}
}
