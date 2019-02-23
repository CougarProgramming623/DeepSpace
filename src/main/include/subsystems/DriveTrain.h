
#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "AHRS.h"
#include <wpi/ArrayRef.h>
#include <wpi/raw_ostream.h>
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
	void ConfigureEncoders();
	void FODDrive(double y, double x, double rotation, double gyroAngle);
	void CartesianDrive(double y, double x, double rotation, double angle);
	int GetTicks();
	double GetLeftVelocity();
	double GetRightVelocity();
};
}//frc2019