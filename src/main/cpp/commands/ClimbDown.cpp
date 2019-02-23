/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbDown.h"
#include "Robot.h"

namespace frc2019 {

ClimbDown::ClimbDown() : m_Timer() {
	Requires(Robot::climb.get());
}

void ClimbDown::Initialize() {
	m_Timer.Start();
	if(Robot::climb->IsLimitHit()) {
		Robot::climb->SetClimbTime(CLIMB_REVERSE_TIME);
	}
}

void ClimbDown::Execute() {
	Robot::climb->SetPower(-1.0);
	double time = m_Timer.Get();
	if(m_LastTime != -1.0) {//If this isnt the first time...
		double delta = time - m_LastTime;
		Robot::climb->SubtractClimbTime(delta);
		if(Robot::climb->GetClimbTime()  < 0.0) {
			Robot::climb->ResetClimbTime();
		}
	}
	m_LastTime = time;

}

bool ClimbDown::IsFinished() {
	return Robot::climb->GetClimbTime() > 0.0;//We are done once we have reversed the climb time for the length of time we need
}

void ClimbDown::End() {
	Robot::climb->SetPower(0.0);
}

void ClimbDown::Interrupted() {

}



}//namespace
