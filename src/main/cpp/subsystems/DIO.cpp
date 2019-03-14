/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DIO.h"
namespace frc2019 {
DIO::DIO() : Subsystem("DIO Reader"), dioInput(0) {}

void DIO::InitDefaultCommand(){
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
bool DIO::GetState() {
	return DIO::m_isTriggered;
}
void DIO::SetState(bool newState) {
	DIO::m_isTriggered = newState;
}
bool DIO::GetDIO()
{
	return dioInput.Get();
}
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
