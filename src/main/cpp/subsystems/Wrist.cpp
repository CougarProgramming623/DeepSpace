/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Wrist.h"
#include "RobotConstants.h"
#include "TalonConfig.h"

namespace frc2019 {

Wrist::Wrist() : Subsystem("Wrist"), wristMC(WRIST_ID) {
  initialReading = wristMC.GetSelectedSensorPosition();
  wristMC.SetSelectedSensorPosition(wristMC.GetSelectedSensorPosition());
  wristMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 10);
  wristMC.ConfigNominalOutputForward(0, 30);
  wristMC.ConfigNominalOutputReverse(0, 30);
  wristMC.ConfigPeakOutputForward(-1, 30);
  wristMC.ConfigPeakOutputReverse(-1, 30);
  wristMC.Config_kF(0, 0.0, 30);
  wristMC.Config_kP(0, 3.0, 30);
  wristMC.Config_kI(0, 0.0, 0);
  wristMC.Config_kD(0, 0.0, 0);
}

void Wrist::InitDefaultCommand() {
  
}

int Wrist::GetWristTalonData(TalonData data) {
  using namespace talon;
  return GetTalonData(&wristMC, data);
}

void Wrist::SetSetpoint(int setpoint) {
  wristMC.Set(ControlMode::Position, initialReading + setpoint);
  frc::SmartDashboard::PutNumber("Wrist Target", wristMC.GetClosedLoopTarget());
  frc::SmartDashboard::PutNumber("Wrist Error", wristMC.GetClosedLoopError());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
}