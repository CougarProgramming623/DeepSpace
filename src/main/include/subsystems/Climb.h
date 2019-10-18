#pragma once

#include <frc/commands/Subsystem.h>

#include <ctre/Phoenix.h>

//The number of seconds the motor should be run backward to release the spring that beings the back peg-leg up
#define CLIMB_REVERSE_TIME 0.5

#define CLIMB_UP_SPEED -1.0
#define CLIMB_DOWN_SPEED 0.25

namespace frc2019 {


class Climb : public frc::Subsystem {
public:
	Climb();

	inline bool IsLimitHit() const { return m_HitLimit; }
	inline bool SetLimitHit(bool limit) { m_HitLimit = limit; }
	
	inline void StopClimbMotor() { m_ClimbMotor.Set(0.0); }
	void SetClimbUpPower();
	void SetClimbDownPower();

	void InitDefaultCommand() override;
private:
	bool m_HitLimit = false;//TODO set this when we detect the limit switch has been triggered
	WPI_TalonSRX m_ClimbMotor;
	WPI_TalonSRX m_ClimbAssistMotor;
	double m_ClimbTime = 0.0;//The number of seconds the climb motor has been running forward for

};

}//namespace 