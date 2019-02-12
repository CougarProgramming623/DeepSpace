/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Wrist.h"

namespace frc2019 {

Wrist::Wrist() : Subsystem("Wrist"), wristMC(2) {
  wristMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 10);
}

void Wrist::InitDefaultCommand() {
  
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
}