/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetWristPosition.h"
#include "Robot.h"
namespace frc2019{
SetWristPosition::SetWristPosition(int setpoint) : m_setpoint(setpoint), m_dialPosition(DialPosition::INVALID) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::wrist.get());
}

SetWristPosition::SetWristPosition(DialPosition position) : m_dialPosition(position) {}

// Called just before this Command runs the first time
void SetWristPosition::Initialize() {
	if(m_setpoint > Robot::wrist->GetWristTalonData(TalonData::SENSOR_POSITION))
		Robot::wrist->SetP(UP_kP_WRIST);
	else
		Robot::wrist->SetP(DOWN_kP_WRIST);
	if (m_dialPosition != DialPosition::INVALID) {
		m_setpoint = Robot::arm->GetWristPosition(m_dialPosition, Robot::oi->IsCargoMode());
	}
	DriverStation::ReportError("Wrist going to: " + std::to_string(m_setpoint));
	Robot::wrist->SetSetpoint(m_setpoint);
}

// Called repeatedly when this Command is scheduled to run
void SetWristPosition::Execute() {
    SmartDashboard::PutNumber("wrist error", Robot::wrist->GetWristTalonData(TalonData::ERROR));
}

// Make this return true when this Command no longer needs to run execute()
bool SetWristPosition::IsFinished() { return true; }

// Called once after isFinished returns true
void SetWristPosition::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetWristPosition::Interrupted() {}
}
