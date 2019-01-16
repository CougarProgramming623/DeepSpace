/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"
#include "commands/Drive.h"

#include <frc/DriverStation.h>

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	mLeftFrontMC	.reset(new WPI_TalonSRX(15));
	mRightFrontMC	.reset(new WPI_TalonSRX( 4));
	mLeftRearMC		.reset(new WPI_TalonSRX( 3));
	mRightRearMC	.reset(new WPI_TalonSRX( 7));
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

void DriveTrain::fodDrive(double y, double x, double rot, double angle)
{
	mMecanumDrive->DriveCartesian(y, x, rot, angle);
}

