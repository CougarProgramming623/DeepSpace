/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "subsystems/Arm.h"
#include "Robot.h"

namespace frc2019 {

class ArmControl : public frc::Command {
 public:
  ArmControl(double speed);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 public:
  static std::shared_ptr<Arm> arm;
private:
   double m_speed;

};
}