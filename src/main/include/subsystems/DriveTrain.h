
#pragma once

#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "AHRS.h"

#include <frc/commands/Subsystem.h>

namespace frc2019 {

class DriveTrain : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<WPI_TalonSRX> mLeftFrontMC, mRightFrontMC;
	std::shared_ptr<WPI_TalonSRX> mLeftRearMC, mRightRearMC;
	std::shared_ptr<frc::MecanumDrive> mMecanumDrive;

public:
	DriveTrain();
	void InitDefaultCommand() override;
	void FODDrive(double x, double y, double rotation, double gyroAngle);
	//int GetTicks();
};


}//frc2019