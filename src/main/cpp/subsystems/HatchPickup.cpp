/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPickup.h"

HatchPickup::HatchPickup() : Subsystem("ExampleSubsystem"), pickupMC(100) {
  pickupMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 10);
}

void HatchPickup::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

int HatchPickup::GetPotData() {
  return pickupMC.GetSensorCollection().GetAnalogIn();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
