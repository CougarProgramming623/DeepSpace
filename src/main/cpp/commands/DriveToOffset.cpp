
#include "commands/DriveToOffset.h"
#include "Constants.h"
#include <frc/DriverStation.h>
#include "Vec.h"
#include "Robot.h"
#include "Cob.h"
#include "CobConstants.h"

#include <algorithm>


namespace frc2019 {


	double LeftWheelEncoderSource::PIDGet() {
		return Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION);
	}

	LeftWheelEncoderSource source;

	void DriveToOffset::Initialize() {
		Requires(Robot::driveTrain.get()); //dependent on the Drivetrain subsystem
		Robot::driverHasControl = false;
		double p = Cob::GetValue<double>(COB_TURN_P);
		double i = Cob::GetValue<double>(COB_TURN_I);
		double d = Cob::GetValue<double>(COB_TURN_D);

		frc::DriverStation::ReportError("Turn p: " + std::to_string(p) + ", i: " + std::to_string(i) + ", d: " + std::to_string(d));

		m_TurnController.reset(new PIDController(p, i, d, Robot::navx.get(), this)); //initializes a PIDController with a kP, kI, kD, PIDSource, and PIDOuput
		m_TurnController->SetInputRange(-180.0f, 180.0f); //sets input range to an angle
		m_TurnController->SetOutputRange(-1.0, 1.0); //sets output range to a motor power
		m_TurnController->SetAbsoluteTolerance(2.0f); //makes it so the robot ends at most 2 degrees of its target angle
		m_TurnController->SetSetpoint(m_Target.z + Robot::navx.get()->GetYaw()); //sets target angle
		m_TurnController->SetContinuous(true);
		m_TurnController->Enable();

		double strafeP = Cob::GetValue<double>(COB_STRAFE_P);
		double strafeI = Cob::GetValue<double>(COB_STRAFE_I);
		double strafeD = Cob::GetValue<double>(COB_STRAFE_D);
		frc::DriverStation::ReportError("Strafe p: " + std::to_string(strafeP) + ", i: " + std::to_string(strafeI) + ", d: " + std::to_string(strafeD));

		double initalTicks = Robot::driveTrain->GetDriveTalonData(DriveTalon::LEFT_REAR, TalonData::SENSOR_POSITION);
		double delta = GetDriveError().x;
		double ticks = initalTicks + delta;

		m_StrafeController.reset(new PIDController(strafeP, strafeI, strafeD, &source, this)); //initializes a PIDController with a kP, kI, kD, PIDSource, and PIDOuput
		m_StrafeController->Disable();
		m_StrafeController->SetInputRange(std::min(initalTicks, ticks), std::max(initalTicks, ticks));
		m_StrafeController->SetOutputRange(-1.0, 1.0); //sets output range to a motor power
		m_StrafeController->SetAbsoluteTolerance(5.0f); //makes it so the robot ends at 2 encoder ticks off
		m_StrafeController->SetSetpoint(ticks); //Calculate actual value in ticks
		m_StrafeController->SetContinuous(true);

		DriverStation::ReportError("Starting DriveToOffset");
	}
	
	void DriveToOffset::Execute() {
		m_Position.z = Robot::navx.get()->GetYaw();
		if (m_Status == VisionStatus::ROTATE) {
			frc::DriverStation::ReportError("Current angle: " + std::to_string(m_Position.z));

			Robot::driveTrain->CartesianDrive(0, 0, m_PIDOut, Robot::navx.get()->GetYaw());
			
			double error = GetDriveError().z;
			DriverStation::ReportError("Turn error: " + std::to_string(error));
			if (abs(error) < 2) {
				m_Status = VisionStatus::STRAFE;//Move on to the next phase
				m_TurnController->Disable();
				m_StrafeController->Enable();
				DriverStation::ReportError("Switching to strafe phase");
			}
		} else if (m_Status == VisionStatus::STRAFE) {

			Robot::driveTrain->CartesianDrive(0, m_PIDOut, 0, 0);

			DriverStation::ReportError("Strafing");
		}
	}

	bool DriveToOffset::IsFinished() {
		return m_Status == VisionStatus::APPROACH;
	}


	void DriveToOffset::End() {
		Robot::driverHasControl = true;
	}

	void DriveToOffset::Interrupted() {

	}

	void DriveToOffset::PIDWrite(double output) {
		m_PIDOut = output;
	}

}

