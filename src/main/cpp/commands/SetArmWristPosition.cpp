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
  switch(height) {
    case RocketHeight::LOW_HATCH:
      AddParallel(new SetArmPosition(84));
      AddSequential(new SetWristPosition(195));
    case RocketHeight::MEDIUM_HATCH:
      AddParallel(new SetArmPosition(203));
      AddSequential(new SetWristPosition(323));
    case RocketHeight::HIGH_HATCH:
      AddParallel(new SetArmPosition(315));
      AddSequential(new SetWristPosition(421));
    default:
      AddParallel(new SetArmPosition(Robot::arm->GetArmTalonData(TalonData::SENSOR_POSITION)));
      AddSequential(new SetWristPosition(Robot::wrist->GetWristTalonData(TalonData::SENSOR_POSITION)));

  }
}
}
