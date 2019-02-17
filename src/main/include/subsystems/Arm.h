/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/WPILib.h>

namespace frc2019 {
class Arm : public frc::Subsystem {
public:
  Arm();
  void InitDefaultCommand() override;
  void SetSetpoint(int setpoint);
  int GetPositionData();
private:
  TalonSRX armMC;
  int initialReading;
};
}
