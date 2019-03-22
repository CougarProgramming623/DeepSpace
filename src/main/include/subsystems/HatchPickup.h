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

#define FORK_SETPOINT_FILE_NAME "/home/lvuser/ForkSetpoints.bin" 
namespace frc2019 {
class HatchPickup : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	TalonSRX pickupMC;
	int initialReading;
	std::string m_CobNames[FORK_SETPOINT_COUNT];
	int m_fork_setpoints[FORK_SETPOINT_COUNT] {};//Main Arm vs Wrist, Cargo vs Hatch, arm positions
	int forkOffset[1] {};
private:
	std::string MakeCOBAddress(int setpoint);
public:
	HatchPickup();
	void InitDefaultCommand() override;
	void SetSetpoint(int);
	void SetVelocity(double);
	int GetForkTalonData(TalonData);
	int GetSetpoint(ForkSetpoints setpoint);
	void PullSetpoints();
	void SaveSetpoints();
	inline int GetOffset() { return forkOffset[0]; }
};

}
