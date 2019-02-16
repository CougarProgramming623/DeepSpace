/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "commands/ArmMovement.h"
#include "Robot.h"
#include "ctre/Phoenix.h"
namespace frc2019{

std::shared_ptr<frc::AnalogPotentiometer> ArmMovement::wristPot;
std::shared_ptr<frc::AnalogInput> ArmMovement::wristAnalogInput;
std::shared_ptr<frc::AnalogPotentiometer> ArmMovement::elbowPot;
std::shared_ptr<frc::AnalogInput> ArmMovement::elbowAnalogInput;
std::shared_ptr<frc::AnalogPotentiometer> ArmMovement::forkliftPot;
std::shared_ptr<frc::AnalogInput> ArmMovement::forkliftAnalogInput;


dumbOutput ArmMovement::wristOutput;
superDumbOutput ArmMovement::elbowOutput;

frc::PIDController* ArmMovement::elbowPID;
frc::PIDController* ArmMovement::wristPID;
frc::PIDController* ArmMovement::forkliftPID;
int ArmMovement::state;

volatile double ArmMovement::wristPower;
volatile double ArmMovement::elbowPower;
volatile double ArmMovement::forkliftPower;

void dumbOutput::PIDWrite(double output){
  ArmMovement::wristPower = output;
}
void superDumbOutput::PIDWrite(double output){
  ArmMovement::elbowPower = output;
}
ArmMovement::ArmMovement() : frc::Command(), frc::PIDOutput(){
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::arm.get());
}

// Called just before this Command runs the first time
void ArmMovement::Initialize() {
  /*
  state = 0; //change this to whatever dial the knob is on
  //CHANGE PORTS  
  wristAnalogInput.reset(new AnalogInput(0));
  elbowAnalogInput.reset(new AnalogInput(1));
  forkliftAnalogInput.reset(new AnalogInput(2));

  wristPot.reset(new AnalogPotentiometer(wristAnalogInput, 1.0, 0.0));
  elbowPot.reset(new AnalogPotentiometer(elbowAnalogInput, 1.0, 0.0));
  forkliftPot.reset(new AnalogPotentiometer(forkliftAnalogInput, 1.0, 0.0));

  wristPID = new frc::PIDController(0.0, 0.0, 0.0, &wristPot, &wristOutput);
  elbowPID = new frc::PIDController(0.0, 0.0, 0.0, &elbowPot, &elbowOutput);
  forkliftPID = new frc::PIDController(0.0, 0.0, 0.0, &forkliftPot, this);

  wristPID->Enable();
  elbowPID->Enable();
  forkliftPID->Enable();
  */
}

// Called repeatedly when this Command is scheduled to run
void ArmMovement::Execute() {
  //drive talons
  
}

// Make this return true when this Command no longer needs to run execute()
bool ArmMovement::IsFinished() { return false; }

// Called once after isFinished returns true
void ArmMovement::End() {
  /*
  DriverStation::ReportError("PID Disabled");
  wristPID->Disable();
  elbowPID->Disable();
  forkliftPID->Disable();
  */
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmMovement::Interrupted() {}

void ArmMovement::PIDWrite(double output){
  //ArmMovement::forkliftPower = output;
}
}