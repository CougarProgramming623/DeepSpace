/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "AHRS.h"

#include <frc/commands/Subsystem.h>

class DriveTrain : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<WPI_TalonSRX> mLeftFrontMC, mRightFrontMC;
	std::shared_ptr<WPI_TalonSRX> mLeftRearMC, mRightRearMC;
	std::shared_ptr<frc::MecanumDrive> mMecanumDrive;

public:
	DriveTrain();
	void InitDefaultCommand() override;
	void fodDrive(double, double, double, double);
	std::shared_ptr<AHRS> getNavx();
};
