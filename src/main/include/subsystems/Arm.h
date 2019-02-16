/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#define ELBOWID 0 //change for whatever port talon
#define WRISTID 0 //change for whatever port talon

#include <frc/commands/Subsystem.h>
#include "frc/WPILib.h"

namespace frc2019{
  class Arm : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  /*
  std::shared_ptr<frc::WPI_TalonSRX> wrist;
	std::shared_ptr<frc::WPI_TalonSRX> elbow;
  */

 public:
  Arm();
  void InitDefaultCommand() override;
};

}
