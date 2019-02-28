/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Arm.h"
#include "RobotConstants.h"
#include "TalonConfig.h"

namespace frc2019 {
Arm::Arm() : Subsystem("Arm"), armMC(ARM_TALON_ID) {
  using namespace talon;
  ConfigurePotentiometer(&armMC, 10, 0.0, 0.0, 0.5, -0.3);
}

void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  //SetDefaultCommand(new SetArmPosition(0));
}

double Arm::GetArmTalonData(TalonData data) {
  using namespace talon;
  return GetTalonData(&armMC, data);
}

void Arm::SetSetpoint(int setpoint) {
  armMC.Set(ControlMode::Position, setpoint);
  frc::SmartDashboard::PutNumber("Arm Target", armMC.GetClosedLoopTarget());
  frc::SmartDashboard::PutNumber("Arm Error", armMC.GetClosedLoopError());
}

void Arm::SetP(double kP) {
  armMC.Config_kP(0, kP, 30);
}
}//namespace
