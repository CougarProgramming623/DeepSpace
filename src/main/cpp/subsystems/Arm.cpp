/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Arm.h"
#include "commands/ArmMovement.h"

namespace frc2019{
  Arm::Arm() : Subsystem("Arm") {
    wrist.reset(new WPI_TalonSRX(WRISTID));
    elbow.reset(new WPI_TalonSRX(ELBOWID));
    forklift.reset(new WPI_TalonSRX(FORKLIFTID));
  }

  void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
    
    
    SetDefaultCommand(new ArmMovement());
  }

// Put methods for controlling this subsystem
// here. Call these from Commands.  
}

