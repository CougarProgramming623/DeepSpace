/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vacuum.h"
#include "RobotConstants.h"

#define SUCK_SPEED 0.5

namespace frc2019 {
Vacuum::Vacuum() : Subsystem("Vacuum"), vacuumMC(VACUUM_ID), servo(0) {

} //Vacuum()

void Vacuum::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
} //InitDefaultCommand()

void Vacuum::Suck() {
  vacuumMC.Set(ControlMode::PercentOutput, 1.0);
} //SetVacuumSpeed()

void Vacuum::Stop() {
  vacuumMC.Set(ControlMode::PercentOutput, 0.0);
}
void Vacuum::SetServoPosition(double pos) {
  servo.SetPosition(pos);
}

double Vacuum::GetServoPosition() {
  return servo.GetPosition();
}
} //frc2019