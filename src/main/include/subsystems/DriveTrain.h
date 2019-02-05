
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
	WPI_TalonSRX m_LeftFrontMC, m_RightFrontMC;
	WPI_TalonSRX m_LeftRearMC, m_RightRearMC;
	frc::MecanumDrive m_MecanumDrive;

public:
	DriveTrain();
	void InitDefaultCommand() override;
	void FODDrive(double x, double y, double rotation, double gyroAngle);
	//int GetTicks();
};


}//frc2019