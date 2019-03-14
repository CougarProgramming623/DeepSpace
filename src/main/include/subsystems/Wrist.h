/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "GameEnums.h"
#include "RobotConstants.h"
#include "TalonConfig.h"
namespace frc2019 {

class Wrist : public frc::Subsystem {
public:
	Wrist();
	void InitDefaultCommand() override;
	void SetP(double);
	void SetSetpoint(int);
	void SetVelocity(float);
	int GetWristPosition();

	int GetCargoPosition(DialPosition position);
	int GetHatchPosition(DialPosition position);

	int GetPosition(DialPosition position, CargoOrHatch cargo);
	int GetOffset();

	double GetWristTalonData(TalonData);
private:
	TalonSRX wristMC;
};


}