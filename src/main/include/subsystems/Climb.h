
#include <frc/commands/Subsystem.h>

#include <ctre/Phoenix.h>

//The number of seconds the motor should be run backward to release the spring that beings the back peg-leg up
#define CLIMB_REVERSE_TIME 0.5

namespace frc2019 {

//Weather or not we hit the hard limit while climbing (true when we climb to the top)

class Climb : public frc::Subsystem {
public:
	Climb() = default;//Use default constructor
	bool IsLimitHit() const;
	void SetPower(double power);
	void SetClimbTime(double time);
	void AddClimbTime(double delta);
	double GetClimbTime() const;
	void Climb::ResetClimbTime();

private:
	bool m_HitLimit = false;
	WPI_TalonSRX m_ClimbMotor;
	double m_ClimbTime = 0.0;//The number of seconds the climb motor has been running forward for

};

}//namespace