/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbUp.h"
#include "Robot.h"
#include <frc/WPILib.h>

namespace frc2019 {

ClimbUp::ClimbUp() : m_Timer() {
	Requires(Robot::climb.get());
}

void ClimbUp::Initialize() {
	m_Timer.Start();
	frc::DriverStation::ReportError("Starting climb up");
}

void ClimbUp::Execute() {
	Robot::climb->SetClimbUpPower();
	Robot::climb->SetClimbTime(m_Timer.Get());//Count the time we climbed for
	frc::DriverStation::ReportError("Executing Climb up...");
	//This means that the peg legs have deployed and we can no longer safley climb down
	//We can only run the climb motor backwords to retarct the last peg-leg 
	//if(m_Timer.Get() > CRITICAL_CLIMB_TIME) {
	//	Robot::climb->SetLimitHit(true);
	//}
}

bool ClimbUp::IsFinished() {
	return false;// FIXME return true if we detect the hard limit of the climb motor
}

void ClimbUp::End() {
	Robot::climb->StopClimbMotor();
}

void ClimbUp::Interrupted() {

}
}//namespace