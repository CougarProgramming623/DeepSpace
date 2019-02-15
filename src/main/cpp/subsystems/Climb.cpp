
#include "subsystems/Climb.h"

namespace frc2019 {

//Weather or not we hit the hard limit while climbing (true when we climb to the top)

bool Climb::IsLimitHit() const {
	return m_HitLimit;
}

void Climb::SetPower(double power) {
	m_ClimbMotor.Set(power);
}

void Climb::SetClimbTime(double time) {
	m_ClimbTime = time;
}

void Climb::AddClimbTime(double delta) {
	m_ClimbTime += delta;
}

double Climb::GetClimbTime() const {
	return m_ClimbTime;
}

void Climb::ResetClimbTime() {
	m_ClimbTime = 0.0;
}

}//namespace
