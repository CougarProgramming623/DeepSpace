/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vacuum.h"
#include "RobotConstants.h"
#include "Cob.h"
#include "CobConstants.h"

#define SUCK_SPEED 0.5

namespace frc2019 {
Vacuum::Vacuum() : Subsystem("Vacuum"), vacuumMC(VACUUM_ID), servo(CARGO_HATCH_SERVO_ID) {
	vacuumMC.ConfigContinuousCurrentLimit(30, 20);
	vacuumMC.EnableCurrentLimit(true);
} //Vacuum()

void Vacuum::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
} //InitDefaultCommand()

void Vacuum::Suck() {
  vacuumMC.Set(ControlMode::PercentOutput, 1.0);
  Cob::PushValue(COB_VACUUM, true);
  
} //Suck()

void Vacuum::Stop() {
  vacuumMC.Set(ControlMode::PercentOutput, 0.0);
  Cob::PushValue(COB_VACUUM, false);
}

void Vacuum::SetServoPosition(double pos) {
  servo.SetPosition(pos);
  if (pos == 0.0) {
	  Cob::PushValue(COB_HATCH, true);
  } else {
	  Cob::PushValue(COB_HATCH, false);
  }
}

double Vacuum::GetServoPosition() {
  return servo.GetPosition();
}

double Vacuum::GetCurrent() {
	return vacuumMC.GetOutputCurrent();
}

void Vacuum::Update() {
	Cob::PushValue(COB_IS_HOLDING, vacuumMC.GetOutputCurrent() < 27 && vacuumMC.GetOutputCurrent() > 20);
	DriverStation::ReportError(std::to_string(vacuumMC.GetOutputCurrent()));
}

bool Vacuum::IsSucking() {
	return vacuumMC.GetMotorOutputPercent() > 0.75f;
}
} //frc2019