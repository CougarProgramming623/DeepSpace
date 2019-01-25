
#include "subsystems/DriveTrain.h"
#include "commands/Drive.h"
#include "RobotConstants.h"

#include <frc/DriverStation.h>

namespace frc2019 {

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	mLeftFrontMC.reset(new WPI_TalonSRX(LEFT_FRONT_ID));
	mRightFrontMC.reset(new WPI_TalonSRX(RIGHT_FRONT_ID));
	mLeftRearMC.reset(new WPI_TalonSRX(LEFT_BACK_ID));
	mRightRearMC.reset(new WPI_TalonSRX(RIGHT_BACK_ID));
	mMecanumDrive.reset(new frc::MecanumDrive(*mLeftFrontMC, *mRightFrontMC,*mLeftRearMC, *mRightRearMC));
	mMecanumDrive->SetExpiration(0.1);
	mMecanumDrive->SetSafetyEnabled(false);
	mMecanumDrive->SetMaxOutput(1.0);
	DriverStation::ReportError("Creating Drive Train!");
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new Drive());
}

void DriveTrain::fodDrive(double y, double x, double rotation, double gyroAngle) {
	mMecanumDrive->DriveCartesian(y, x, rotation, gyroAngle);
}


}//frc2019