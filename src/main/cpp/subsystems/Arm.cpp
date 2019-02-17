/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Arm.h"
#include "RobotConstants.h"
#include "commands/SetArmPosition.h"

namespace frc2019 {
Arm::Arm() : Subsystem("Arm"), armMC(ARM_TALON_ID) {
  armMC.SetSelectedSensorPosition(armMC.GetSelectedSensorPosition());
  initialReading = armMC.GetSelectedSensorPosition();
  armMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 30); //configure the potentiometer connected to the arm TalonSRX
  armMC.ConfigNominalOutputForward(0, 30);
	armMC.ConfigNominalOutputReverse(0, 30);
	armMC.ConfigPeakOutputForward(1, 30);		
  armMC.ConfigPeakOutputReverse(-1, 30);
  
  /* set closed loop gains in slot0 */
	armMC.Config_kF(0, 0.0, 30);
	armMC.Config_kP(0, 3.0, 30);
	armMC.Config_kI(0, 0.0, 30);
	armMC.Config_kD(0, 0.0, 30);
}



void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  //SetDefaultCommand(new SetArmPosition(0));
}

int Arm::GetPositionData() {
  return armMC.GetSelectedSensorPosition(0); //return the potentiometer reading
}

void Arm::SetSetpoint(int setpoint) {
  armMC.Set(ControlMode::Position, initialReading + setpoint);
  frc::SmartDashboard::PutNumber("Error", armMC.GetClosedLoopError());
  frc::SmartDashboard::PutNumber("Target", armMC.GetClosedLoopTarget());
  frc::SmartDashboard::PutNumber("trajectory", armMC.GetActiveTrajectoryPosition());  
}
}//namespace
