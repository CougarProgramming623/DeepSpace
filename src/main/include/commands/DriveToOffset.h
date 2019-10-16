
#pragma once

#include <memory>

#include <frc/commands/Command.h>

#include "Vec.h"
#include "PID.h"
using namespace ohs623;

namespace frc2019 {

class DriveToOffset : public frc::Command {
public:
	DriveToOffset() {}

	//Callers can mutate target and position
	inline Vec3& GetTarget() { return m_Target; } 
	inline Vec3& GetPosition() { return m_Position; }

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	//X and Y are on the plane of the field in feet, and Z is rotation in degrees where counter clockwise is positive 
	Vec3 m_Target = {0, 0, 0};
	Vec3 m_Position = {0, 0, 0};
	std::unique_ptr<OHSPIDController> m_Controller;
};

}
