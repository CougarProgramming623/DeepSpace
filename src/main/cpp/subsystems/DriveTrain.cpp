
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
	//mLeftRearMC->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 1, 5);
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new Drive());
}

void DriveTrain::FODDrive(double y, double x, double rotation, double gyroAngle) {
	mMecanumDrive->DriveCartesian(y, x, rotation, gyroAngle);
}

void DriveTrain::RODrive(double x, double y, double rotation){
	mMecanumDrive->DriveCartesian(x, y, rotation);
}
/*
int DriveTrain::GetTicks() {
	return mLeftRearMC->GetSelectedSensorPosition(1);
}
*/
}//frc2019