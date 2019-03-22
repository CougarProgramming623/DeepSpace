/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPickup.h"
#include "RobotConstants.h"
#include "TalonConfig.h"
#include "commands/SetForkPosition.h"
#include "GameEnums.h"
#include "Cob.h"

#define kPID_LOOP_IDX 0
#define kTIMEOUT_MS 30

namespace frc2019 {
HatchPickup::HatchPickup() : Subsystem("ExampleSubsystem"), pickupMC(FORK_ID) {
	pickupMC.SetSelectedSensorPosition(pickupMC.GetSelectedSensorPosition()); //set the position as 0
	pickupMC.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, kPID_LOOP_IDX, kTIMEOUT_MS); //configure FeedbackDevice as Analog
	pickupMC.ConfigNominalOutputForward(0, kTIMEOUT_MS);
	pickupMC.ConfigNominalOutputReverse(0, kTIMEOUT_MS);
	pickupMC.ConfigPeakOutputForward(0.75, kTIMEOUT_MS); //configure the peak output forward	
	pickupMC.ConfigPeakOutputReverse(-0.5, kTIMEOUT_MS); //configure the peak output reverse
	//configure P I D values for the potentiometer
	pickupMC.Config_kF(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);
	pickupMC.Config_kP(kPID_LOOP_IDX, 5.0, kTIMEOUT_MS);
	pickupMC.Config_kI(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);
	pickupMC.Config_kD(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);
	
	for(int i = 0; i < FORK_SETPOINT_COUNT; i++) {
		ForkSetpoints setpoint = static_cast<ForkSetpoints>(i);
		m_CobNames[i] = MakeCOBAddress(i);
	}

	FILE* file = fopen(FORK_SETPOINT_FILE_NAME, "rb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Fork setpoint file doesn't exist! Make sure to se defaults using the COB");
		memset(forkOffset, sizeof(forkOffset), 0x00);
	} else {
		frc::DriverStation::ReportError("Fork setpoint file found!");
		fread(m_fork_setpoints, sizeof(m_fork_setpoints), 1, file);
		fread(forkOffset, sizeof(forkOffset), 1, file);
		fclose(file);
	}

	for(int i = 0; i < FORK_SETPOINT_COUNT; i++) {
		Cob::PushValue(m_CobNames[i], m_fork_setpoints[i]);
	}

	Cob::PushValue(COB_SAVE_FORK_SETPOINTS, false);
	Cob::PushValue(COB_PULL_FORK_SETPOINTS, false);
	Cob::PushValue(COB_FORK_OFFSET, forkOffset[0]);
	frc::DriverStation::ReportError("Created fork network tables");


} //HatchPickup()

void HatchPickup::InitDefaultCommand() {
	// Set the default command for a subsystem here.
    //SetDefaultCommand(new SetForkPosition(pickupMC.GetSelectedSensorPosition()));
} //InitDefaultCommand()

int HatchPickup::GetForkTalonData(TalonData data) {
	using namespace talon;
	return GetTalonData(&pickupMC, data);
} //GetForkTalonData()

int HatchPickup::GetSetpoint(ForkSetpoints setpoint) {
	return m_fork_setpoints[setpoint];
}
void HatchPickup::SetVelocity(double velocity) {
	pickupMC.Set(ControlMode::PercentOutput, velocity);
}

void HatchPickup::SetSetpoint(int setpoint) {
	pickupMC.Set(ControlMode::Position, setpoint); //set the target position of the potentiometer
} //SetSetpoint()

std::string HatchPickup::MakeCOBAddress(int setpoint) {
	std::string result = "fork/setpoints/";
	result += FORK_SETPOINT_NAMES[setpoint];
	return result;
}

void HatchPickup::PullSetpoints() {
	for(int i = 0; i < ARM_MECHANISM_TYPE_COUNT; i++) {
		std::string address = m_CobNames[i]; 
		int newValue = Cob::GetValue<int>(address);
		DriverStation::ReportError("Setting address: " + address + " to " + std::to_string(newValue));
		m_fork_setpoints[i] = newValue;
	}

	forkOffset[0] = Cob::GetValue<int>(COB_FORK_OFFSET);
}

void HatchPickup::SaveSetpoints() {
	frc::DriverStation::ReportError("Calling SaveSetpoints()");
	FILE* file = fopen(FORK_SETPOINT_FILE_NAME, "wb");
	if(file == nullptr) {
		frc::DriverStation::ReportError("Error creating fork setpoints file: " FORK_SETPOINT_FILE_NAME);
	} else {
		fwrite(m_fork_setpoints, sizeof(m_fork_setpoints), 1, file);
		fwrite(forkOffset, sizeof(forkOffset), 1, file);
		fclose(file);
		frc::DriverStation::ReportError("Saved fork setpoints successfully!");
	}
}
} //frc2019

