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
#include "Wrist.h"

#define EXTRA_ARRAY_LENGTH 8

#define EXTRA_ARRAY_ACTUAL_LENGTH 2
const constexpr char * const EXTRA_NAMES[] = {"arm-position/offset", "wrist-position/offset"};

#define ARM_OFFSET_INDEX 0
#define WRIST_OFFSET_INDEX 1

#define ARM_SETPOINT_FILE_NAME "/home/lvuser/ArmSetpoints.bin"

namespace frc2019 {
class Arm : public frc::Subsystem {
	friend class Wrist;
public:
	Arm();
	void InitDefaultCommand() override;
	void SetP(double);
	void SetSetpoint(int);
	void SetVelocity(float);

	int GetArmTalonData(TalonData);
	inline int GetCargoPosition(DialPosition position) { return m_setpoints[ArmMechanismType::MAIN_ARM][CargoOrHatch::CARGO][(int) position] + GetOffset(); }
	inline int GetHatchPosition(DialPosition position) { return m_setpoints[ArmMechanismType::MAIN_ARM][CargoOrHatch::HATCH][(int) position] + GetOffset(); }
	
	inline int GetPosition(DialPosition position, CargoOrHatch cargo) { return m_setpoints[ArmMechanismType::MAIN_ARM][(int) cargo][(int) position] +  + GetOffset(); }
	
	void PullSetpoints();
	void SaveSetpoints();

	inline int GetOffset() { return m_extra[ARM_OFFSET_INDEX]; }

private:
	std::string MakeCOBAddress(ArmMechanismType arm, CargoOrHatch cargoOrHatch, DialPosition position);

private:
	TalonSRX armMC;
	int initialReading;
	std::string m_CobNames[ARM_MECHANISM_TYPE_COUNT][CARGO_OR_HATCH_COUNT][DIAL_POSITION_COUNT];
	int m_setpoints[ARM_MECHANISM_TYPE_COUNT][CARGO_OR_HATCH_COUNT][DIAL_POSITION_COUNT] {};//Main Arm vs Wrist, Cargo vs Hatch, arm positions
	int m_extra[EXTRA_ARRAY_LENGTH];
};


}//namespace
