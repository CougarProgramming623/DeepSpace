/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <stdio.h>

#include <frc/WPILib.h>
#include <frc/DriverStation.h>

#include "subsystems/Arm.h"
#include "commands/SetArmPosition.h"
#include "RobotConstants.h"
#include "TalonConfig.h"

#include "GameEnums.h"
#include "Cob.h"
#include "CobConstants.h"

namespace frc2019 {
Arm::Arm() : Subsystem("Arm"), armMC(ARM_TALON_ID) {

	using namespace talon;
	ConfigurePotentiometer(&armMC, 20, 0.0, 25, 0.75, -0.3);

	for(int armI = 0; armI < ARM_MECHANISM_TYPE_COUNT; armI++) {
		for(int cargoI = 0; cargoI < CARGO_OR_HATCH_COUNT; cargoI++) {
			for(int positionI = 0; positionI < DIAL_POSITION_COUNT; positionI++) {
				ArmMechanismType arm = static_cast<ArmMechanismType>(armI);
				CargoOrHatch cargo = static_cast<CargoOrHatch>(cargoI);
				DialPosition position = static_cast<DialPosition>(positionI);
				m_CobNames[arm][cargo][position] = MakeCOBAddress(arm, cargo, position);
			}
		}
	}

	FILE* file = fopen(ARM_SETPOINT_FILE_NAME, "rb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Arm setpoint file doesn't exist! Make sure to se defaults using the COB");
		memset(m_extra, sizeof(m_extra), 0x00);
	} else {
		frc::DriverStation::ReportError("Arm setpoint file found!");
		fread(m_setpoints, sizeof(m_setpoints), 1, file);
		fread(m_extra, sizeof(m_extra), 1, file);
		fclose(file);
	}
	for(int armI = 0; armI < ARM_MECHANISM_TYPE_COUNT; armI++) {
		for(int cargoI = 0; cargoI < CARGO_OR_HATCH_COUNT; cargoI++) {
			for(int positionI = 0; positionI < DIAL_POSITION_COUNT; positionI++) {
				ArmMechanismType arm = static_cast<ArmMechanismType>(armI);
				CargoOrHatch cargo = static_cast<CargoOrHatch>(cargoI);
				DialPosition position = static_cast<DialPosition>(positionI);
				Cob::PushValue(m_CobNames[arm][cargo][position], m_setpoints[arm][cargo][position]);
			}
		}
	}
	Cob::PushValue(COB_SAVE_ARM_SETPOINTS, false);
	Cob::PushValue(COB_PULL_ARM_SETPOINTS, false);

	for(int i = 0; i < EXTRA_ARRAY_ACTUAL_LENGTH; i++) {
		std::string address = EXTRA_NAMES[i];
		Cob::PushValue(address, m_extra[i]);
	}
	 

	frc::DriverStation::ReportError("Created inital network tables");

	armMC.Set(ControlMode::Position, armMC.GetSelectedSensorPosition());
}

void Arm::PullSetpoints() {
	for(int armI = 0; armI < ARM_MECHANISM_TYPE_COUNT; armI++) {
		for(int cargoI = 0; cargoI < CARGO_OR_HATCH_COUNT; cargoI++) {
			for(int positionI = 0; positionI < DIAL_POSITION_COUNT; positionI++) {
				std::string address = m_CobNames[armI][cargoI][positionI]; 
				int newValue = Cob::GetValue<int>(address);
				DriverStation::ReportError("Setting address: " + address + " to " + std::to_string(newValue));
				m_setpoints[armI][cargoI][positionI] = newValue;
			}
		}
	}
	for(int i = 0; i < EXTRA_ARRAY_ACTUAL_LENGTH; i++) {
		std::string address = EXTRA_NAMES[i];
		m_extra[i] = Cob::GetValue<int>(address);
	}
}

void Arm::SaveSetpoints() {
	frc::DriverStation::ReportError("Calling SaveSetpoints()");
	FILE* file = fopen(ARM_SETPOINT_FILE_NAME, "wb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Error creating arm setpoints file: " ARM_SETPOINT_FILE_NAME);
	} else {
		fwrite(m_setpoints, sizeof(m_setpoints), 1, file);
		fwrite(m_extra, sizeof(m_extra), 1, file);
		fclose(file);
		frc::DriverStation::ReportError("Saved arm setpoints successfully!");
	}
}

std::string Arm::MakeCOBAddress(ArmMechanismType arm, CargoOrHatch cargoOrHatch, DialPosition position) {
	std::string result;
	if(arm == ArmMechanismType::MAIN_ARM) {
		result += "arm-position/";
	} else if(arm == ArmMechanismType::WRIST) {
		result += "wrist-position/";
	} else { frc::DriverStation::ReportError("Unhandled condition at line " + std::to_string(__LINE__) + " in file " + __FILE__); }
	
	if(cargoOrHatch == CargoOrHatch::HATCH) {
		result += "hatch/";
	} else if(cargoOrHatch == CargoOrHatch::CARGO) {
		result += "cargo/";
	} else { frc::DriverStation::ReportError("Unhandled condition at line " + std::to_string(__LINE__) + " in file " + __FILE__); }
	
	result += DIAL_POSITION_NAMES[position];
	return result;
}

void Arm::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

int Arm::GetArmTalonData(TalonData data) {
	using namespace talon;
	return GetTalonData(&armMC, data);
}

void Arm::SetSetpoint(int setpoint) {
	armMC.Set(ControlMode::Position, setpoint);
	frc::SmartDashboard::PutNumber("Arm Target", armMC.GetClosedLoopTarget());
	frc::SmartDashboard::PutNumber("Arm Error", armMC.GetClosedLoopError());
}

void Arm::SetVelocity(float velocity) {
	armMC.ConfigPeakOutputForward(.75, 30);
	armMC.ConfigPeakOutputReverse(-.3, 30);
	armMC.Set(ControlMode::PercentOutput, velocity);
}

void Arm::SetP(double kP) {
	armMC.Config_kP(0, kP, 30);
}
}//namespace
