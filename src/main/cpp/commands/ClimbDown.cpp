#include "commands/ClimbDown.h"
#include "Robot.h"

namespace frc2019 {

ClimbDown::ClimbDown() : m_Timer() {
	m_Timer.Start();
}

void ClimbDown::Initialize() {
	m_Timer.Start();
}

void ClimbDown::Execute() {
	double now = m_Timer.Get();
	if(Robot::climb.get()->IsLimitHit()) {// We are at the top so run the motor backwards a little
		if(m_Timer.Get() < CLIMB_REVERSE_TIME) {// We need to run the motor back to release the spring
			Robot::climb.get()->SetPower(-1.0);
		} else {
			Robot::climb.get()->SetPower(0.0);// We are done so stop the motor
		}
		
	} else {
		if(Robot::climb.get()->GetClimbTime() > 0.0) {// We still need to reverse the motor
			double delta = now - m_LastTime;
			Robot::climb.get()->AddClimbTime(-delta);// Subtract the time that has passed since last time
			Robot::climb.get()->SetPower(-1.0);// Go backwards
		} 
		if(Robot::climb.get()->GetClimbTime() <= 0.0) {
			Robot::climb.get()->ResetClimbTime();//Go back to zero if we are negitive
			Robot::climb.get()->SetPower(0.0);// We are done so stop the motor
		}
		
	}
	m_LastTime = now;
}


bool ClimbDown::IsFinished() {
	if(Robot::climb.get()->IsLimitHit()) {// We were at the top so run the motor backwards a little to trigger the spring
		return m_Timer.Get() > CLIMB_REVERSE_TIME;// We have reversed for more than the required time, so we are finished
	} else {
		return  Robot::climb.get()->GetClimbTime() == 0.0;// Finish once we have reversed for the required duration
	}
}

void ClimbDown::End() {

}

void ClimbDown::Interrupted() {

}

}//namespace