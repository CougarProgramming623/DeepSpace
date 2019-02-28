/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Wrist.h"

namespace frc2019 {
Wrist::Wrist() : Subsystem("Wrist"), wristMC(WRIST_ID) {
  using namespace talon;
  ConfigurePotentiometer(&wristMC, 5.0, 0.0, 0.0, 1.0, -1.0);
} //Wrist()

void Wrist::InitDefaultCommand() {
  
} //InitDefaultCommand()

void Wrist::SetSetpoint(int setpoint) {
  wristMC.Set(ControlMode::Position, setpoint);
}

double Wrist::GetWristTalonData(TalonData data) {
  return 0.0;
}
} //frc2019