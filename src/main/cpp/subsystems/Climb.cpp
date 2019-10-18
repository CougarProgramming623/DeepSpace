#include "subsystems/Climb.h"
#include "RobotConstants.h"
#include "GameEnums.h"
#include "Cob.h"
#include "commands/StopClimb.h"

#include "Robot.h"

namespace frc2019 {

//Weather or not we hit the hard limit while climbing (true when we climb to the top)
Climb::Climb() : frc::Subsystem("Climb"), m_ClimbMotor(CLIMB_ID), m_ClimbAssistMotor(SLAVE_ID) {

}

void Climb::InitDefaultCommand() {
    m_ClimbAssistMotor.Follow(m_ClimbMotor);
}

void Climb::SetClimbDownPower() {
	if(Robot::oi->CanClimb()) {
		m_ClimbMotor.Set(CLIMB_DOWN_SPEED);
	}
}

void Climb::SetClimbUpPower() {
	if(Robot::oi->CanClimb()) {
		m_ClimbMotor.Set(CLIMB_UP_SPEED);
	}
}

}//namespace