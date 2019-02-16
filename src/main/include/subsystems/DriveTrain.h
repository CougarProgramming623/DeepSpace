
#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "AHRS.h"

#include <frc/commands/Subsystem.h>

namespace frc2019 {

class DriveTrain : public frc::Subsystem {
private:
	WPI_TalonSRX m_LeftFrontMC, m_RightFrontMC;
	WPI_TalonSRX m_LeftRearMC, m_RightRearMC;
	frc::MecanumDrive m_MecanumDrive;

public:
	DriveTrain();
	void InitDefaultCommand() override;
	void FODDrive(double y, double x, double rotation, double gyroAngle);
	int GetTicks();
	int SetSpeed();
};

}//frc2019