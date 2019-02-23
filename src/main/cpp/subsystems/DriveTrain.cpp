
#include "subsystems/DriveTrain.h"
#include "RobotConstants.h"
#include "commands/Drive.h"
#include <frc/DriverStation.h>
#include "Constants.h"
#include "OI.h"

namespace frc2019 {

using namespace ohs623;

DriveTrain::DriveTrain() : Subsystem("DriveTrain"),
	m_LeftFrontMC(LEFT_FRONT_ID),
	m_RightFrontMC(RIGHT_FRONT_ID),
	m_LeftRearMC(LEFT_BACK_ID),
	m_RightRearMC(RIGHT_BACK_ID) {

		//invert the right side due to being a mecanum drive
		m_RightFrontMC.SetInverted(true);
		m_RightRearMC.SetInverted(true);
		
		#ifdef BOT_HAMBONE
		ConfigureEncoders();
		#endif
} //DriveTrain()

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new Drive());
} //InitDefaultCommand()

void DriveTrain::ConfigureEncoders() {
	//configure all four encoders as feedback devices
	m_LeftFrontMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
	m_LeftRearMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
	m_RightFrontMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
	m_RightRearMC.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);

	//configure feed forward gain, kF = 1023 / max encoder velocity
	m_LeftFrontMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);
	m_LeftRearMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);
	m_RightFrontMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);
	m_RightRearMC.Config_kF(0, 1023 / kMAX_VELOCITY, 30);

	//configure proportional, integral, and derivative gains of drive motor controllers
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
} //ConfigureEncoders()

void DriveTrain::CartesianDrive(double y, double x, double rotation, double angle) {
	//source: WPILib
	//same code found in CartesianDrive in the WPI Library but adapted for being used in Velocity Mode
	Vector2d input{x, y};
	input.Rotate(angle);
	double wheelSpeeds[4] ;
	
	wheelSpeeds[kFRONT_LEFT] = input.y + input.x + rotation;
	wheelSpeeds[kFRONT_RIGHT] = input.y - input.x - rotation;
	wheelSpeeds[kREAR_LEFT] = input.y - input.x + rotation;
	wheelSpeeds[kREAR_RIGHT] = input.y + input.x  - rotation;

	Normalize(wheelSpeeds);

	#ifdef BOT_HAMBONE //use velocity mode if using real bot, if samus use percent output


	/*
	if(OI::buttonBoard.GetRawButton(OI_DRIVE_PERCENT_OUTPUT_MODE)) {
		m_LeftFrontMC.Set(ControlMode::PercentOutput, wheelSpeeds[kFRONT_LEFT]);
		m_LeftRearMC.Set(ControlMode::PercentOutput,wheelSpeeds[kREAR_LEFT]);
		m_RightFrontMC.Set(ControlMode::PercentOutput, wheelSpeeds[kFRONT_RIGHT]);
		m_RightRearMC.Set(ControlMode::PercentOutput, wheelSpeeds[kREAR_RIGHT]);
	}
	else {
	*/
		m_LeftFrontMC.Set(ControlMode::Velocity, wheelSpeeds[kFRONT_LEFT] * kMAX_VELOCITY);
		m_LeftRearMC.Set(ControlMode::Velocity,wheelSpeeds[kREAR_LEFT] * kMAX_VELOCITY);
		m_RightFrontMC.Set(ControlMode::Velocity, wheelSpeeds[kFRONT_RIGHT] * kMAX_VELOCITY);
		m_RightRearMC.Set(ControlMode::Velocity, wheelSpeeds[kREAR_RIGHT] * kMAX_VELOCITY);
	//}

	#else
	m_LeftFrontMC.Set(ControlMode::PercentOutput, wheelSpeeds[kFRONT_LEFT]);
	m_LeftRearMC.Set(ControlMode::PercentOutput,wheelSpeeds[kREAR_LEFT]);
	m_RightFrontMC.Set(ControlMode::PercentOutput, wheelSpeeds[kFRONT_RIGHT]);
	m_RightRearMC.Set(ControlMode::PercentOutput, wheelSpeeds[kREAR_RIGHT]);
	#endif
} //CartesianDrive()

void DriveTrain::Normalize(wpi::MutableArrayRef<double> wheelSpeeds) {
  double maxMagnitude = std::abs(wheelSpeeds[0]);
  for (size_t i = 1; i < wheelSpeeds.size(); i++) {
    double temp = std::abs(wheelSpeeds[i]);
    if (maxMagnitude < temp) {
      maxMagnitude = temp;
    }
  }
  if (maxMagnitude > 1) {
    for (size_t i = 0; i < wheelSpeeds.size(); i++) {
      wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
    }
  }
} //Normalize()

int DriveTrain::GetDriveTalonData(DriveTalon driveTalon, TalonData data) {
	using namespace talon;
	switch(driveTalon) {
		case DriveTalon::LEFT_FRONT:
			return GetTalonData(&m_LeftFrontMC, data);
		case DriveTalon::LEFT_REAR:
			return GetTalonData(&m_LeftRearMC, data);
		case DriveTalon::RIGHT_FRONT:
			return GetTalonData(&m_RightFrontMC, data);
		case DriveTalon::RIGHT_REAR:
			return GetTalonData(&m_RightRearMC, data);
		default:
			return 0;
	};
} //GetDriveTalonData()
}//namespace
