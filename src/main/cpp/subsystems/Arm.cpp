/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Arm.h"
#include "RobotConstants.h"

namespace frc2019 {
Arm::Arm() : Subsystem("Arm"), armMC(ARM_TALON_ID) {
  armMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 10); //configure the potentiometer connected to the arm TalonSRX
}



void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

int Arm::GetPotData() {
  return armMC.GetSensorCollection().GetAnalogIn(); //return the potentiometer reading
}
}//namespace
