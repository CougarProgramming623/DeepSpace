/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetManipulator.h"
#include "Robot.h"

namespace frc2019 {

SetManipulator::SetManipulator(Command* onTrue, Command* onFalse) : frc::ConditionalCommand(onTrue, onFalse) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

bool SetManipulator::Condition() {
  return Robot::oi->IsCargoMode();
}
// Make this return true when this Command no longer needs to run execute()
bool SetManipulator::IsFinished() { return true; }

}