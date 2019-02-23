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

Vacuum::Vacuum() : Subsystem("Vacuum"), vacuumMC(VACUUM_ID) {
}

void Vacuum::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Vacuum::SetVacuumSpeed() {
  vacuumMC.Set(ControlMode::PercentOutput, SUCK_SPEED);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
}