/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "AHRS.h"

class Turn : public frc::Command, public frc::PIDOutput {
 public:
    Turn(double);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
    void PIDWrite(double) override;
  private:
    PIDController *turnController;
    double m_angle;
    double rotateToAngleRate;
    AHRS *gyro;


};
