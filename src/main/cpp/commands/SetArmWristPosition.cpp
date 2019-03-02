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
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
  DriverStation::ReportError(std::to_string(height));
  switch(height) {
    case RocketHeight::LOW_HATCH:
      armSetpoint = 84;
      wristSetpoint = 195;
      break;
    case RocketHeight::MEDIUM_HATCH:
      armSetpoint = 203;
      wristSetpoint = 323;
      break;
    case RocketHeight::HIGH_HATCH:
      armSetpoint = 315;
      wristSetpoint = 421;
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
    default:
      break;
  }

  AddParallel(new SetArmPosition(armSetpoint));
  AddSequential(new SetWristPosition(wristSetpoint));
}
}
