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
#include "frc/PIDOutput.h"


namespace frc2019 {

class centerX_Source : public frc::PIDSource {
  public:
    double PIDGet();
};
class width_Source : public frc::PIDSource {
  public:
    double PIDGet();
};

class xOutput : public frc::PIDOutput {
  public:
    void PIDWrite(double output);
};
class yOutput : public frc::PIDOutput{
  public:
    void PIDWrite(double output);
};
class zOutput : public frc::PIDOutput{
  public:
    void PIDWrite(double output);
};

class VisionDrive : public frc::Command {
 public:
  VisionDrive();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  std::shared_ptr<nt::NetworkTable> start_networkTable();
  static std::vector<double> arrCenterX, arrAngle, arrHeight, arrWidth;
  static int correctIndex;
  volatile static double xPower, zPower, yPower;
  static double getCenterX();
  static double getWidth();
  static frc::Preferences* prefs;
  double xP, xI, xD;
  double yP, yI, yD;
  double zP, zI, zD;
  static double targetWidth;
private:

  static centerX_Source xSource;
  static width_Source ySource;
  
  double getClosestTargetAngle();

  static xOutput xOut;
  static yOutput yOut;
  static zOutput zOut;

  static std::shared_ptr<nt::NetworkTable> visionTable;
  void findLeftSignature();
  static frc::PIDController* xPID;
  static frc::PIDController* yPID;
  static frc::PIDController* zPID;
};
}