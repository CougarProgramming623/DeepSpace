/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPickup.h"
#include "RobotConstants.h"
#include "TalonConfig.h"

namespace frc2019 {
HatchPickup::HatchPickup() : Subsystem("ExampleSubsystem"), pickupMC(FORK_ID) {
  using namespace talon;
  ConfigurePotentiometer(&pickupMC, 3.0, 0.0, 0.0, 1.0, -1.0);
} //HatchPickup()

void HatchPickup::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
} //InitDefaultCommand()

int HatchPickup::GetForkTalonData(TalonData data) {
  using namespace talon;
  return GetTalonData(&pickupMC, data);
} //GetForkTalonData()

void HatchPickup::SetSetpoint(int setpoint) {
  pickupMC.Set(ControlMode::Position, setpoint); //set the target position of the potentiometer
} //SetSetpoint()
} //frc2019

