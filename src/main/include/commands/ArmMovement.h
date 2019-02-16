/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "frc/PIDSource.h"
#include "frc/PIDOutput.h"
#include "ctre/Phoenix.h"

namespace frc2019{
  class dumbOutput : public frc::PIDOutput{
    public:
      void PIDWrite(double output);
  };
  class superDumbOutput : public frc::PIDOutput{
    public:
      void PIDWrite(double output);
  };

  class ArmMovement : public frc::Command , frc::PIDOutput{
    public:
      ArmMovement();
      void Initialize() override;
      void Execute() override;
      bool IsFinished() override;
      void End() override;
      void Interrupted() override;
      void PIDWrite(double output) override;
      static int state;

      static dumbOutput wristOutput;
      static superDumbOutput elbowOutput;

      volatile static double wristPower, elbowPower, forkliftPower;
      
    private:
      static frc::PIDController* wristPID;
      static frc::PIDController* elbowPID;
      static frc::PIDController* forkliftPID;
  };
}

