/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Wrist.h"

namespace frc2019 {

Wrist::Wrist() : Subsystem("Wrist"), wristMC(2) {
  wristMC.SetSelectedSensorPosition(wristMC.GetSelectedSensorPosition());
  initialReading = wristMC.GetSelectedSensorPosition();
  wristMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 30); //configure the potentiometer connected to the Wrist TalonSRX
  wristMC.ConfigNominalOutputForward(0, 30);
	wristMC.ConfigNominalOutputReverse(0, 30);
	wristMC.ConfigPeakOutputForward(1, 30);		
  wristMC.ConfigPeakOutputReverse(-1, 30);
  
  /* set closed loop gains in slot0 */
	wristMC.Config_kF(0, 0.0, 30);
	wristMC.Config_kP(0, 3.0, 30);
	wristMC.Config_kI(0, 0.0, 30);
	wristMC.Config_kD(0, 0.0, 30);
}

void Wrist::InitDefaultCommand() {
  
}

int Wrist::GetPositionData() {
  return wristMC.GetSelectedSensorPosition(0); //return the potentiometer reading
}

void Wrist::SetSetpoint(int setpoint) {
  wristMC.Set(ControlMode::Position, initialReading + setpoint);
  frc::SmartDashboard::PutNumber("Error", wristMC.GetClosedLoopError());
  frc::SmartDashboard::PutNumber("Target", wristMC.GetClosedLoopTarget());
  frc::SmartDashboard::PutNumber("trajectory", wristMC.GetActiveTrajectoryPosition());  
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
}