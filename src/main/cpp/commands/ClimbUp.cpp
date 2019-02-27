/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbUp.h"
#include "Robot.h"

namespace frc2019 {

ClimbUp::ClimbUp() : m_Timer() {
	Requires(Robot::climb.get());
}

void ClimbUp::Initialize() {
	m_Timer.Start();
}

void ClimbUp::Execute() {
	Robot::climb->SetPower(1.0);
	Robot::climb->SetClimbTime(m_Timer.Get());//Count the time we climbed for
}

bool ClimbUp::IsFinished() {
	return false;// FIXME return true if we detect the hard limit of the climb motor
}

void ClimbUp::End() {
	Robot::climb->SetPower(0.0);
}

void ClimbUp::Interrupted() {

}



}//namespace
