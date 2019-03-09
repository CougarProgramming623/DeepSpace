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
  ConfigurePotentiometer(&wristMC, 9.0, 0.0, 25.0, 0.4, -0.6);

	wristMC.Set(ControlMode::Position, wristMC.GetSelectedSensorPosition());
} //Wrist()

void Wrist::InitDefaultCommand() {
  
} //InitDefaultCommand()

void Wrist::SetP(double kP) {
	wristMC.Config_kP(0, kP, 30);
}

void Wrist::SetSetpoint(int setpoint) {
	wristMC.Set(ControlMode::Position, setpoint);
}

void Wrist::SetVelocity(float velocity) {
	wristMC.Set(ControlMode::PercentOutput, velocity);
}

void Wrist::GetWristPosition() {
	wristMC.GetSelectedSensorPosition();
}

double Wrist::GetWristTalonData(TalonData data) {
	using namespace talon;
	return GetTalonData(&wristMC, data);
}

} //frc2019