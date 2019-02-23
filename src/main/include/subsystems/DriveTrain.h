
#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "AHRS.h"
#include <wpi/ArrayRef.h>
#include <wpi/raw_ostream.h>
#include <frc/commands/Subsystem.h>
#include "TalonConfig.h"
#include "GameEnums.h"

namespace frc2019 {

class DriveTrain : public frc::Subsystem {
private:
	WPI_TalonSRX m_LeftFrontMC, m_RightFrontMC;
	WPI_TalonSRX m_LeftRearMC, m_RightRearMC;
public:
	DriveTrain();
	void InitDefaultCommand() override;
	void ConfigureEncoders();
	void CartesianDrive(double y, double x, double rotation, double angle);
	void Normalize(wpi::MutableArrayRef<double> wheelSpeeds);
	int GetTicks();
	int GetDriveTalonData(DriveTalon driveTalon, TalonData data);
};
}//frc2019