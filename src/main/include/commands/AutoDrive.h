/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class AutoDrive : public frc::Command {
 public:
  AutoDrive(double, bool);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  private:
  int currentTicks;
  double m_distance;
  bool isStraffing;
};
<<<<<<< HEAD
}
=======
>>>>>>> parent of eb7e6d2... Fixed all compilation errors and added test code for getting data from potentiometer
