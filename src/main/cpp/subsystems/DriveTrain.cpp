
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
		m_RightFrontMC.SetInverted(true);
		m_RightRearMC.SetInverted(true);
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
	Vector2d input{y, x};
	input.Rotate(-angle);
	double wheelSpeeds[4] ;
	
	wheelSpeeds[kFRONT_LEFT] = input.y + input.x + rotation;
	wheelSpeeds[kREAR_LEFT] = input.y - input.x + rotation;
	wheelSpeeds[kFRONT_RIGHT] = input.y - input.x - rotation;
	wheelSpeeds[kREAR_RIGHT] = input.y + input.x  - rotation;

	Normalize(wheelSpeeds);

	m_LeftFrontMC.Set(ControlMode::Velocity, wheelSpeeds[kFRONT_LEFT] * kMAX_VELOCITY);
	m_LeftRearMC.Set(ControlMode::Velocity,wheelSpeeds[kREAR_LEFT] * kMAX_VELOCITY);
	m_RightFrontMC.Set(ControlMode::Velocity, wheelSpeeds[kFRONT_RIGHT] * kMAX_VELOCITY);
	m_RightRearMC.Set(ControlMode::Velocity, wheelSpeeds[kREAR_RIGHT] * kMAX_VELOCITY);

	frc::SmartDashboard::PutNumberArray("Speeds", wheelSpeeds);
}

int DriveTrain::GetTicks() {
	return m_LeftRearMC.GetSelectedSensorPosition(); //return the number of ticks the encoder returns
}
}//frc2019
