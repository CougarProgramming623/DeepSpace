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
  armMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 30); //configure the potentiometer connected to the arm TalonSRX
} //Arm()

void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
} //InitDefaultCommand()

int Arm::GetArmTalonData(TalonData data) {
  using namespace talon;
  return GetTalonData(&armMC, data);
} //GetArmTalonData()
}//frc2019
