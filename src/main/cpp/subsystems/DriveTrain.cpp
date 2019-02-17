
#include "subsystems/DriveTrain.h"
#include "RobotConstants.h"
#include "commands/Drive.h"
#include <frc/DriverStation.h>
#include "Constants.h"

namespace frc2019 {

using namespace ohs623;

DriveTrain::DriveTrain() : Subsystem("DriveTrain"),
	m_LeftFrontMC(LEFT_FRONT_ID),
	m_RightFrontMC(RIGHT_FRONT_ID),
	m_LeftRearMC(LEFT_BACK_ID),
	m_RightRearMC(RIGHT_BACK_ID),
	m_MecanumDrive(m_LeftFrontMC, m_LeftRearMC, m_RightFrontMC, m_RightRearMC) {

		m_MecanumDrive.SetSafetyEnabled(false);
		m_MecanumDrive.SetMaxOutput(1.0);
		m_MecanumDrive.SetExpiration(0.1);
		/*
			m_RightFrontMC.SetInverted(true);
			m_RightRearMC.SetInverted(true);
		*/
		ConfigureEncoders();
	}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new Drive());
}

void DriveTrain::FODDrive(double y, double x, double rotation, double gyroAngle) {
	m_MecanumDrive.DriveCartesian(y, x, rotation, gyroAngle); //Cartesian Mecanum Drive with the option for Field Oriented Drive
}

void DriveTrain::ConfigureEncoders() {
	m_LeftFrontMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
	m_LeftRearMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
	m_RightFrontMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
	m_RightRearMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);

	m_LeftFrontMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);
	m_LeftRearMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);
	m_RightFrontMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);
	m_RightRearMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);

	m_LeftFrontMC.Config_kP(0, 2.58, 30);
	m_LeftFrontMC.Config_kI(0, 0.0, 30);
	m_LeftFrontMC.Config_kD(0, 40.0, 30);

	m_RightFrontMC.Config_kP(0, 2.58, 30);
	m_RightFrontMC.Config_kI(0, 0.0, 30);
	m_RightFrontMC.Config_kD(0, 40.0, 30);

	m_LeftRearMC.Config_kP(0, 2.58, 30);
	m_LeftRearMC.Config_kI(0, 0.0, 30);
	m_LeftRearMC.Config_kD(0, 40.0, 30);
		
	m_RightRearMC.Config_kP(0, 2.58, 30);
	m_RightRearMC.Config_kI(0, 0.0, 30);
	m_RightRearMC.Config_kD(0, 40.0, 30);
}
void DriveTrain::CartesianDrive(double y, double x, double rotation, double angle) {

	if(abs(x) > kMAX_VELOCITY || abs(y) > kMAX_VELOCITY)
		x = x < 0 ? -1 : 1 * kMAX_VELOCITY;

	Vector2d input{y, x};
	input.Rotate(-angle);
	double wheelSpeeds[4] ;
	
	wheelSpeeds[0] = y + x + rotation;
	wheelSpeeds[1] = y - x + rotation;
	wheelSpeeds[2] = y - x - rotation;
	wheelSpeeds[3] = y + x  - rotation;

	Normalize(wheelSpeeds);

	m_LeftFrontMC.Set(ControlMode::Velocity, wheelSpeeds[0]);
	m_LeftRearMC.Set(ControlMode::Velocity,wheelSpeeds[1]);
	m_RightFrontMC.Set(ControlMode::Velocity, wheelSpeeds[2]);
	m_RightRearMC.Set(ControlMode::Velocity, wheelSpeeds[3]);

	frc::SmartDashboard::PutNumberArray("Speeds", wheelSpeeds);
}

int DriveTrain::GetTicks() {
	return m_LeftRearMC.GetSelectedSensorPosition(); //return the number of ticks the encoder returns
}
}//frc2019
