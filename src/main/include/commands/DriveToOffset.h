
#pragma once

#include <memory>

#include <frc/commands/Command.h>
#include <frc/PIDController.h>

#include "Vec.h"
using namespace ohs623;

namespace frc2019 {

enum VisionStatus {
	ROTATE, STRAFE, APPROACH
};

class DriveToOffset : public frc::Command, public frc::PIDOutput {
public:
	DriveToOffset() {}

	//Callers can mutate target and position
	inline Vec3& GetTarget() { return m_Target; } 
	inline Vec3& GetPosition() { return m_Position; }

	inline Vec3 GetDriveError() { return m_Target - m_Position; }

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	void PIDWrite(double value) override; //comes from PIDOutput class

private:
	//X and Y are on the plane of the field in feet, and Z is rotation in degrees where counter clockwise is positive 
	Vec3 m_Target = {0, 0, 30};
	Vec3 m_Position = {0, 0, 0};
	std::unique_ptr<frc::PIDController> m_TurnController;
	std::unique_ptr<frc::PIDController> m_StrafeController;
	double m_PIDOut = 0.0;
	VisionStatus m_Status = ROTATE;
};

}
