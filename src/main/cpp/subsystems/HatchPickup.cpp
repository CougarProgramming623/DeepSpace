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
HatchPickup::HatchPickup() : Subsystem("ExampleSubsystem"), pickupMC(13) {
  using namespace talon;
  initialReading = pickupMC.GetSelectedSensorPosition(0); //initialReading = home setting of the fork
  ConfigurePotentiometer(&pickupMC, 3.0, 0.0, 0.0);
  /*
  pickupMC.SetSelectedSensorPosition(pickupMC.GetSelectedSensorPosition()); 
  pickupMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 30); //configure potentiometer as a FeedbackDevice on the TalonSRX
  pickupMC.ConfigNominalOutputForward(0, 30);
	pickupMC.ConfigNominalOutputReverse(0, 30);
	pickupMC.ConfigPeakOutputForward(1.0, 30); //set the peak output in the forward direction
  pickupMC.ConfigPeakOutputReverse(-1.0, 30); //set the peak output in the reverse direction
  //configure PID values for the TalonSRX
  pickupMC.Config_kF(0, 0.0, 30); 
  pickupMC.Config_kP(0, 3.0, 30);
  pickupMC.Config_kI(0, 0.0, 30);
  pickupMC.Config_kD(0, 0.0, 30);
  */
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
  pickupMC.Set(ControlMode::Position, setpoint); //set the target position of the potentiometer
  frc::SmartDashboard::PutNumber("Target", GetForkTalonData(TalonData::TARGET));
  frc::SmartDashboard::PutNumber("Error", GetForkTalonData(TalonData::ERROR));
}
} //namespace

