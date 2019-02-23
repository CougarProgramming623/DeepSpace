#include <frc/commands/Subsystem.h>

#include <ctre/Phoenix.h>

//The number of seconds the motor should be run backward to release the spring that beings the back peg-leg up
#define CLIMB_REVERSE_TIME 0.5

namespace frc2019 {

class Climb : public frc::Subsystem {
public:
	Climb();

	inline bool IsLimitHit() const {
		return m_HitLimit;
	}
	inline void SetPower(double power) {
		m_ClimbMotor.Set(power);
	}
	inline void SetClimbTime(double time) {
		m_ClimbTime = time;
	}
	inline void AddClimbTime(double delta) {
		m_ClimbTime += delta;
	}
	inline void SubtractClimbTime(double delta) {
		m_ClimbTime += delta;
	}
	inline double GetClimbTime() const {
		return m_ClimbTime;
	}
	inline void ResetClimbTime() {
		m_ClimbTime = 0.0;
	}

private:
	bool m_HitLimit = false;//TODO set this when we detect the limit switch has been triggered
	WPI_TalonSRX m_ClimbMotor;
	double m_ClimbTime = 0.0;//The number of seconds the climb motor has been running forward for

};

}//namespace 