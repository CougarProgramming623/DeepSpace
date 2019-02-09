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
#include "frc/PIDSource.h"


namespace frc2019 {
class geoffrey : public frc::PIDSource {
  public:
    double PIDGet();
};
class FakePIDOutput;
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
  static std::vector<double> arrCenterX, arrAngle, arrHeight, arrWidth;
  static int correctIndex;
  volatile static double xPower, zPower, yPower;
  static double getPower();
  static void getXPower();
  double rotationRate;
private:
  static geoffrey geoff;
  
  static std::shared_ptr<nt::NetworkTable> visionTable;

	void getZPower(); 
  void getYPower();
  bool somethingWrong();
  static frc::PIDController* zRot;
  static frc::PIDController* xRot;
  FakePIDOutput rotOutput;
  double xDisplacement;
  
};
class FakePIDOutput : public frc::PIDOutput{
  public:
    FakePIDOutput(VisionDrive& visiondrive);
    void PIDWrite(double output);
  private:
    VisionDrive& visionDrive;
};
}
