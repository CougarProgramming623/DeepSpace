/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/ConditionalCommand.h>
#include <frc/WPILib.h>

namespace frc2019 {

class SetManipulator : public frc::ConditionalCommand {
 public:
  SetManipulator(Command* onTrue, Command* onFalse);
  bool Condition() override;
  bool IsFinished() override;
};
}