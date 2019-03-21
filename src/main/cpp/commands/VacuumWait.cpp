/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VacuumWait.h"
#include "Robot.h"
#include "OI.h"

namespace frc2019 {
VacuumWait::VacuumWait() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
	Requires(Robot::vacuum.get());
}

// Called just before this Command runs the first time
void VacuumWait::Initialize() {
	m_timer.Reset();
	m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void VacuumWait::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool VacuumWait::IsFinished() { 
	DriverStation::ReportError(OI::buttonBoard.GetRawButton(1) ? "True" : "False");
	if(OI::buttonBoard.GetRawButton(1)) {
		if(m_timer.Get() > 2.0) {
			m_timer.Stop();
			return true;
		}
	} else {
		return true;
	}
}

// Called once after isFinished returns true
void VacuumWait::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VacuumWait::Interrupted() {}
}