/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "networktables/NetworkTableInstance.h"

namespace frc2019 {
class VisionDrive : public frc::Command, frc::PIDOutput {
 public:
  VisionDrive();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  void PIDWrite(double output) override;
  std::shared_ptr<nt::NetworkTable> start_networkTable();
private:
  std::shared_ptr<nt::NetworkTable> visionTable;
  double getXPower();
	double getZPower(); 
  frc::PIDController* turnController;
  double rotationRate;
  
};
}
