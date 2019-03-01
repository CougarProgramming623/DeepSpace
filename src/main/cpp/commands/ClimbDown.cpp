/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbDown.h"
#include "Robot.h"
#include <frc/WPILib.h>

namespace frc2019 {

ClimbDown::ClimbDown() : m_Timer() {
	Requires(Robot::climb.get());
}

void ClimbDown::Initialize() {
	m_Timer.Start();
	if(Robot::climb->IsLimitHit()) {
		Robot::climb->SetClimbTime(CLIMB_REVERSE_TIME);
		frc::DriverStation::ReportError("CLimb down hit limit");
	} else {
		frc::DriverStation::ReportError("Climb down non limit...");
	}
}

void ClimbDown::Execute() {
	Robot::climb->SetClimbDownPower();
	double time = m_Timer.Get();
	if(m_LastTime != -1.0) {//If this isnt the first time...
		double delta = time - m_LastTime;
		Robot::climb->SubtractClimbTime(delta);
		if(Robot::climb->GetClimbTime() < 0.0) {
			Robot::climb->ResetClimbTime();
		}
	}
	m_LastTime = time;
	frc::DriverStation::ReportError("Executing Climb down...");
}

bool ClimbDown::IsFinished() {
	return Robot::climb->GetClimbTime() > 0.0;//We are done once we have reversed the climb time for the length of time we need
}

void ClimbDown::End() {
	Robot::climb->StopClimbMotor();
}

void ClimbDown::Interrupted() {

}



}//namespace
