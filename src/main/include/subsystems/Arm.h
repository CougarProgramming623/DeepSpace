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

namespace frc2019 {
class Arm : public frc::Subsystem {
public:
	Arm();
	void InitDefaultCommand() override;
	void SetP(double);
	void SetSetpoint(int);
	int GetArmTalonData(TalonData);

	inline int GetWristCargoPosition(DialPosition position) { return m_Setpoints[ArmMechanismType::WRIST][CargoOrHatch::CARGO][position]; }
	inline int GetWristHatchPosition(DialPosition position) { return m_Setpoints[ArmMechanismType::WRIST][CargoOrHatch::HATCH][position]; }

	inline int GetArmCargoPosition(DialPosition position) { return m_Setpoints[ArmMechanismType::MAIN_ARM][CargoOrHatch::CARGO][position]; }
	inline int GetArmHatchPosition(DialPosition position) { return m_Setpoints[ArmMechanismType::MAIN_ARM][CargoOrHatch::HATCH][position]; }
	void PullSetpoints();
	void SaveSetpoints();

private:
	std::string MakeCOBAddress(ArmMechanismType arm, CargoOrHatch cargoOrHatch, DialPosition position);

private:
	TalonSRX armMC;
	int initialReading;
	int m_Setpoints[ARM_MECHANISM_TYPE_COUNT][CARGO_OR_HATCH_COUNT][DIAL_POSITION_COUNT] {};//Main Arm vs Wrist, Cargo vs Hatch, arm positions
};
} //frc2019
