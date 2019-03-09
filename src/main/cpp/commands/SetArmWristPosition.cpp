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
      armSetpoint = 81;
      wristSetpoint = 183;
      break;
    case RocketHeight::MEDIUM_HATCH:
      armSetpoint = 199;
      wristSetpoint = 323-15;
      break;
    case RocketHeight::HIGH_HATCH:
      armSetpoint = 315+10;
      wristSetpoint = 429;
      break;
    case RocketHeight::LOW_CARGO:
      armSetpoint = 61+7;
      wristSetpoint = 80;
      break;
    case RocketHeight::MEDIUM_CARGO:
      armSetpoint = 197;
      wristSetpoint = 203;
      break;
    case RocketHeight::HIGH_CARGO:
      wristSetpoint = 312;
      armSetpoint = 316;
      break;
    case RocketHeight::SHIP_CARGO:
      armSetpoint = 203-15;
      wristSetpoint = 323-25;
      break;
    case RocketHeight::ALL_IN:
      armSetpoint = 0;
      wristSetpoint = 0;
      break;
    case RocketHeight::CARGO_PICKUP:
      armSetpoint = 68;
      wristSetpoint = 304;
      break;
    default:
      break;
  }

  //AddSequential(new frc::WaitCommand(0.25)); //to allow for the transition between buttons on the dial
  if(height == RocketHeight::ALL_IN) {
    AddSequential(new SetWristPosition(113 + wristSetpoint));
    AddSequential(new frc::WaitCommand(1));
    AddSequential(new SetArmPosition(103 + armSetpoint));
  } else if(height == RocketHeight::CARGO_PICKUP) {
    AddSequential(new SetArmPosition(103 + armSetpoint));
    AddSequential(new frc::WaitCommand(1));
    AddSequential(new SetWristPosition(113 + wristSetpoint));
  } else {
    AddParallel(new SetArmPosition(103 + armSetpoint));
    AddSequential(new SetWristPosition(113 + wristSetpoint));
  }
}
}