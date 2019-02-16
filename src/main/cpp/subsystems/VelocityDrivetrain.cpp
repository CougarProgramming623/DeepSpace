/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/VelocityDrivetrain.h"
#include "RobotConstants.h"
#include "commands/VDTest.h"

namespace frc2019 {
VelocityDrivetrain::VelocityDrivetrain() : Subsystem("ExampleSubsystem"), 
                                          leftFront(LEFT_FRONT_ID),
                                          leftRear(LEFT_BACK_ID),
                                          rightFront(RIGHT_FRONT_ID),
                                          rightRear(RIGHT_BACK_ID) 
{
  rightFront.SetInverted(true);
  //rightRear.SetInverted(true);
  leftFront.Follow(leftRear);
  rightFront.Follow(rightRear);
  ConfigureSensors();
  l_maxError = r_maxError = 0;
}

void VelocityDrivetrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new VDTest());
}

void VelocityDrivetrain::ConfigureSensors() {
  leftRear.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
  rightRear.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);

  leftRear.SetSensorPhase(false);
  
  leftRear.Config_kF(0, 1023 * 1 / kMAX_VELOCITY_LEFT, 30);
  rightRear.Config_kF(0, 1023 * 1 / kMAX_VELOCITY_RIGHT, 30);
  
  leftRear.Config_kP(0, 2.58, 30);
  leftRear.Config_IntegralZone(0, 25, 30);
  leftRear.Config_kI(0, 0.0, 30);
  leftRear.Config_kD(0, 40, 30); 

  rightRear.Config_kP(0, 2.58, 30);
  rightRear.Config_IntegralZone(0, 25, 30);
  rightRear.Config_kI(0, 0.0, 30);
  rightRear.Config_kD(0, 40, 30);
}

void VelocityDrivetrain::VelocityDrive(double velocity) {
  //frc::SmartDashboard::PutNumber("Left V", leftrear);
  //frc::SmartDashboard::PutNumber("Right V", velocity);
  leftRear.Set(ControlMode::Velocity, velocity);
  rightRear.Set(ControlMode::Velocity, velocity);

  //if(leftRear.GetClosedLoopError() > l_maxError)
    //l_maxError = leftRear.GetClosedLoopError();
  frc::SmartDashboard::PutNumber("Velocity Left", leftRear.GetSelectedSensorVelocity());
  frc::SmartDashboard::PutNumber("Error Left", l_maxError);

  //if(rightRear.GetClosedLoopError() > r_maxError)
    //r_maxError = rightRear.GetClosedLoopError();

  frc::SmartDashboard::PutNumber("Velocity Right", rightRear.GetSelectedSensorVelocity());
  frc::SmartDashboard::PutNumber("Error Right", r_maxError);

  frc::SmartDashboard::PutNumber("Output left", leftRear.GetMotorOutputPercent());
  frc::SmartDashboard::PutNumber("Output right", rightRear.GetMotorOutputPercent());

  frc::SmartDashboard::PutNumber("difference", leftRear.GetSelectedSensorVelocity() - rightRear.GetSelectedSensorVelocity());
  }

int VelocityDrivetrain::GetVelocity(bool isLeft) {
  return leftRear.GetClosedLoopError();
}
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
