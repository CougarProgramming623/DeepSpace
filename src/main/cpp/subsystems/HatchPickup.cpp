/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPickup.h"
#include "RobotConstants.h"
#include "TalonConfig.h"
#include "commands/SetForkPosition.h"

#define kPID_LOOP_IDX 0
#define kTIMEOUT_MS 30

namespace frc2019 {
HatchPickup::HatchPickup() : Subsystem("ExampleSubsystem"), pickupMC(FORK_ID) {
  pickupMC.SetSelectedSensorPosition(pickupMC.GetSelectedSensorPosition()); //set the position as 0
  pickupMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, kPID_LOOP_IDX, kTIMEOUT_MS); //configure FeedbackDevice as Analog
  pickupMC.ConfigNominalOutputForward(0, kTIMEOUT_MS);
	pickupMC.ConfigNominalOutputReverse(0, kTIMEOUT_MS);
	pickupMC.ConfigPeakOutputForward(0.75, kTIMEOUT_MS); //configure the peak output forward	
  pickupMC.ConfigPeakOutputReverse(-0.5, kTIMEOUT_MS); //configure the peak output reverse
  //configure P I D values for the potentiometer
  pickupMC.Config_kF(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);
  pickupMC.Config_kP(kPID_LOOP_IDX, 5.0, kTIMEOUT_MS);
  pickupMC.Config_kI(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);
  pickupMC.Config_kD(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);

  //pickupMC.Set(ControlMode::Position, pickupMC.GetSelectedSensorPosition());
} //HatchPickup()

void HatchPickup::InitDefaultCommand() {
  // Set the default command for a subsystem here.
    //SetDefaultCommand(new SetForkPosition(pickupMC.GetSelectedSensorPosition()));
} //InitDefaultCommand()

int HatchPickup::GetForkTalonData(TalonData data) {
  using namespace talon;
  return GetTalonData(&pickupMC, data);
} //GetForkTalonData()

void HatchPickup::SetSetpoint(int setpoint) {
  pickupMC.Set(ControlMode::Position, setpoint); //set the target position of the potentiometer
} //SetSetpoint()
} //frc2019

