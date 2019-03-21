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

namespace frc2019 {

class Vacuum : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  TalonSRX vacuumMC;
  frc::Servo servo;
 public:
  Vacuum();
  void InitDefaultCommand() override;
  void Suck();
  void SetServoPosition(double);
  void Stop();
  double GetServoPosition();
  double GetCurrent();
  void Update();

  bool IsSucking();
};
}