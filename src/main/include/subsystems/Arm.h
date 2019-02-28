/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "GameEnums.h"

namespace frc2019 {
class Arm : public frc::Subsystem {
public:
  Arm();
  void InitDefaultCommand() override;
  void SetSetpoint(int);
  void SetP(double);
  double GetArmTalonData(TalonData);
private:
  TalonSRX armMC;
};
} //frc2019
