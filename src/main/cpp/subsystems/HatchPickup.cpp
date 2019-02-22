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
  initialReading = pickupMC.GetSelectedSensorPosition(0);
  pickupMC.SetSelectedSensorPosition(pickupMC.GetSelectedSensorPosition(0));
  pickupMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 10);
  pickupMC.ConfigNominalOutputForward(0, 30);
	pickupMC.ConfigNominalOutputReverse(0, 30);
	pickupMC.ConfigPeakOutputForward(1, 30);		
  pickupMC.ConfigPeakOutputReverse(-1, 30);
  pickupMC.Config_kF(0, 0.0, 30);
  pickupMC.Config_kP(0, 2.0, 30);
  pickupMC.Config_kI(0, 0.0, 30);
  pickupMC.Config_kD(0, 0.0, 30);
}

void HatchPickup::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

int HatchPickup::GetForkTalonData(TalonData data) {
  using namespace talon;
  return GetTalonData(&pickupMC, data);
}

void HatchPickup::SetSetpoint(int setpoint) {
  pickupMC.Set(ControlMode::Position, initialReading + setpoint);
  frc::SmartDashboard::PutNumber("Fork Target", pickupMC.GetClosedLoopTarget());
  frc::SmartDashboard::PutNumber("Fork Error", pickupMC.GetClosedLoopError());
}

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
