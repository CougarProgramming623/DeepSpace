/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetArmWristPosition.h"
#include "commands/SetArmPosition.h"
#include "commands/SetWristPosition.h"
#include "Robot.h"

namespace frc2019 {
SetArmWristPosition::SetArmWristPosition(RocketHeight height) {
  Requires(Robot::arm.get());
  Requires(Robot::wrist.get());
  
  DriverStation::ReportError(std::to_string(height));
  switch(height) {
    case RocketHeight::LOW_HATCH:
      armSetpoint = 84;
      wristSetpoint = 192 - 10;
      break;
    case RocketHeight::MEDIUM_HATCH:
      armSetpoint = 203+10;
      wristSetpoint = 323+10-10;
      break;
    case RocketHeight::HIGH_HATCH:
      armSetpoint = 315+10;
      wristSetpoint = 421+10-10-10-10;
      break;
    case RocketHeight::LOW_CARGO:
      armSetpoint = 61+7;
      wristSetpoint = 80;
      break;
    case RocketHeight::MEDIUM_CARGO:
      armSetpoint = 177+5;
      wristSetpoint = 173;
      break;
    case RocketHeight::HIGH_CARGO:
      wristSetpoint = 312;
      armSetpoint = 316;
      break;
    case RocketHeight::SHIP_CARGO:
      armSetpoint = 203-15;
      wristSetpoint = 323-25;
    case RocketHeight::ALL_IN:
      armSetpoint = 0;
      wristSetpoint = 0;
    default:
      break;
  }

  //AddSequential(new frc::WaitCommand(0.25)); //to allow for the transition between buttons on the dial
  if(height == RocketHeight::ALL_IN) {
    AddSequential(new SetWristPosition(123 + wristSetpoint));
    AddSequential(new frc::WaitCommand(1));
    AddSequential(new SetArmPosition(108 + armSetpoint));
  } else {
    AddParallel(new SetArmPosition(108 + armSetpoint));
    AddSequential(new SetWristPosition(123 + wristSetpoint));
  }
}
}