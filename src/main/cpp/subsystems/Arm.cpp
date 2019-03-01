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
#include "RobotConstants.h"
#include "TalonConfig.h"

#include "GameEnums.h"
#include "Cob.h"
#include "CobConstants.h"

namespace frc2019 {
Arm::Arm() : Subsystem("Arm"), armMC(ARM_TALON_ID) {

	using namespace talon;
	ConfigurePotentiometer(&armMC, 10, 0.0, 0.0, 0.5, -0.3);

	FILE* file = fopen(ARM_SETPOINT_FILE_NAME, "rb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Arm setpoint file doesn't exist! Make sure to se defaults using the COB");
	} else {
		frc::DriverStation::ReportError("Arm setpoint file found!");
		fread(m_Setpoints, sizeof(m_Setpoints), 1, file);
		fclose(file);
	}
	for(int armI = 0; armI < ARM_MECHANISM_TYPE_COUNT; armI++) {
		for(int cargoI = 0; cargoI < CARGO_OR_HATCH_COUNT; cargoI++) {
			for(int positionI = 0; positionI < DIAL_POSITION_COUNT; positionI++) {
				ArmMechanismType arm = static_cast<ArmMechanismType>(armI);
				CargoOrHatch cargo = static_cast<CargoOrHatch>(cargoI);
				DialPosition position = static_cast<DialPosition>(positionI);
				Cob::PushValue(MakeCOBAddress(arm, cargo, position), m_Setpoints[arm][cargo][position]);
			}
		}
	}
	Cob::PushValue(COB_SAVE_ARM_SETPOINTS, false);
	Cob::PushValue(COB_PULL_ARM_SETPOINTS, false);
	frc::DriverStation::ReportError("Created inital network tables");
}

void Arm::PullSetpoints() {
	for(int armI = 0; armI < ARM_MECHANISM_TYPE_COUNT; armI++) {
		for(int cargoI = 0; cargoI < CARGO_OR_HATCH_COUNT; cargoI++) {
			for(int positionI = 0; positionI < DIAL_POSITION_COUNT; positionI++) {
				std::string address = MakeCOBAddress(static_cast<ArmMechanismType>(armI), static_cast<CargoOrHatch>(cargoI), static_cast<DialPosition>(positionI));
				int newValue = Cob::GetValue<int>(address);
				DriverStation::ReportError("Setting address: " + address + " to " + std::to_string(newValue));
				m_Setpoints[armI][cargoI][positionI] = newValue;
			}
		}
	}
}

void Arm::SaveSetpoints() {
	frc::DriverStation::ReportError("Calling SaveSetpoints()");
	FILE* file = fopen(ARM_SETPOINT_FILE_NAME, "wb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Error creating arm setpoints file: " ARM_SETPOINT_FILE_NAME);
	} else {
		fwrite(m_Setpoints, sizeof(m_Setpoints), 1, file);
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
	//SetDefaultCommand(new SetArmPosition(0));
}

int Arm::GetArmTalonData(TalonData data) {
	using namespace talon;
	return GetTalonData(&armMC, data);
}

void Arm::SetSetpoint(int setpoint) {
	armMC.Set(ControlMode::Position, initialReading + setpoint);
	frc::SmartDashboard::PutNumber("Arm Target", armMC.GetClosedLoopTarget());
	frc::SmartDashboard::PutNumber("Arm Error", armMC.GetClosedLoopError());
}

void Arm::SetP(double kP) {
  armMC.Config_kP(0, kP, 30);
}


}//namespace
