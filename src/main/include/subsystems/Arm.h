/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

namespace frc2019 {
class Arm : public frc::Subsystem {
public:
  Arm();
  void InitDefaultCommand() override;
  int GetPotData();
private:
  TalonSRX armMC;
};
}
