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
  wristMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 30);
} //Wrist()

void Wrist::InitDefaultCommand() {
  
} //InitDefaultCommand()
} //frc2019