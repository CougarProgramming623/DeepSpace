
#include "subsystems/DriveTrain.h"
#include "RobotConstants.h"
#include "commands/Drive.h"

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
		m_LeftRearMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 1, 5); //sets up encoder on left rear TalonSRX
	}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new Drive());
}

void DriveTrain::FODDrive(double y, double x, double rotation, double gyroAngle) {
	m_MecanumDrive.DriveCartesian(y, x, rotation, gyroAngle); //Cartesian Mecanum Drive with the option for Field Oriented Drive
}

int DriveTrain::GetTicks() {
	return m_LeftRearMC.GetSelectedSensorPosition(); //return the number of ticks the encoder returns
}

int DriveTrain::SetSpeed() {
	return 0;
}
}//frc2019
