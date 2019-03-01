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
	initialReading = armMC.GetSelectedSensorPosition();
	armMC.SetSelectedSensorPosition(armMC.GetSelectedSensorPosition());
	armMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 30); //configure the potentiometer connected to the arm TalonSRX
	armMC.ConfigNominalOutputForward(0, 30);
	armMC.ConfigNominalOutputReverse(0, 30);
	armMC.ConfigPeakOutputForward(1, 30);
	armMC.ConfigPeakOutputReverse(-1, 30);
	armMC.Config_kF(0, 0.0, 30);
	armMC.Config_kP(0, 3.0, 30);
	armMC.Config_kI(0, 0.0, 30);
	armMC.Config_kD(0, 0.0, 30);

	FILE* file = fopen(ARM_SETPOINT_FILE_NAME, "rb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Arm setpoint file doesn't exist! Make sure to se defaults using the COB");
	} else {
		frc::DriverStation::ReportError("Arm setpoint file found!");
		fread(m_Setpoints, sizeof(m_Setpoints), 1, file);
		fclose(file);
		for(ArmMekanismType arm = 0; arm < ARM_MEKANISM_TYPE_COUNT; arm++) {
			for(CargoOrHatch cargo = 0; cargo < CARGO_OR_HATCH_COUNT; cargo++) {
				for(DialPosition position = 0; position < DIAL_POSITION_COUNT; position++) {
					Cob::PushValue(MakeCOBAddress(arm, cargo, position), m_Setpoints[arm][cargo][position]);
				}
			}
		}

	}


}

Arm::~Arm() {
	FILE* file = fopen(ARM_SETPOINT_FILE_NAME, "wb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Error creating arm setpoints file!");
	} else {
		fwrite(m_Setpoints, sizeof(m_Setpoints), 1, file);
		fclose(file);
		frc::DriverStation::ReportError("Saved arm setpoints successfully!");
	}
}

std::string Arm::MakeCOBAddress(ArmMekanismType arm, CargoOrHatch cargoOrHatch, DialPosition position) {
	std::string result;
	if(arm == ArmMekanismType::MAIN_ARM) {
		result += "arm-position/";
	} else if(arm == ArmMekanismType::WRIST) {
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


}//namespace
