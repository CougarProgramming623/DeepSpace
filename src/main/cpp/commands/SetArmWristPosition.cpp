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
  bool isCargoMode = Robot::oi->IsCargoMode();

  DriverStation::ReportError(std::to_string(height));
  switch(height) {
    case RocketHeight::LOW:
      armSetpoint = isCargoMode ? 61+7 : 84;
      wristSetpoint = isCargoMode ? 80 : 182;
      break;
    case RocketHeight::MEDIUM:
      armSetpoint = isCargoMode ? 177+5 : 213;
      wristSetpoint = isCargoMode ? 173 : 323-10+10;
      break;
    case RocketHeight::HIGH:
      armSetpoint = isCargoMode ? 316 : 325;
      wristSetpoint = isCargoMode ? 312 : 421+10-10-10-10;
      break;
    case RocketHeight::SHIP:
      armSetpoint = isCargoMode ? 203-15 : 84;
      wristSetpoint = isCargoMode ? 323-25 : 182;
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