
#include "subsystems/DriveTrain.h"
#include "commands/Drive.h"
#include "RobotConstants.h"

#include <frc/DriverStation.h>

namespace frc2019 {

DriveTrain::DriveTrain() : Subsystem("DriveTrain"),
	m_LeftFrontMC(LEFT_FRONT_ID),
	m_RightFrontMC(RIGHT_FRONT_ID),
	m_LeftRearMC(LEFT_BACK_ID),
	m_RightRearMC(RIGHT_BACK_ID),
	m_MecanumDrive(m_LeftFrontMC, m_RightFrontMC, m_LeftRearMC, m_RightRearMC) {

		m_MecanumDrive.SetExpiration(0.1);
		m_MecanumDrive.SetSafetyEnabled(false);
		m_MecanumDrive.SetMaxOutput(1.0);
		//mLeftRearMC->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 1, 5);
	}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new Drive());
}

void DriveTrain::FODDrive(double y, double x, double rotation, double gyroAngle) {
	m_MecanumDrive.DriveCartesian(y, x, rotation, gyroAngle);
}

int DriveTrain::GetTicks() {
	return abs(m_LeftRearMC.GetSelectedSensorPosition(1));
}
}//frc2019
