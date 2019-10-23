
#include "commands/DriveToOffset.h"
#include "Constants.h"
#include <frc/DriverStation.h>
#include "Vec.h"
#include "Robot.h"
#include "Cob.h"
#include "CobConstants.h"

namespace frc2019 {

	void DriveToOffset::Initialize() {
		Requires(Robot::driveTrain.get()); //dependent on the Drivetrain subsystem
		double p = Cob::GetValue<double>(COB_TURN_P);
		double i = Cob::GetValue<double>(COB_TURN_I);
		double d = Cob::GetValue<double>(COB_TURN_D);

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

		m_StrafeController.reset(new PIDController(strafeP, strafeI, strafeD, Robot::navx.get(), this)); //initializes a PIDController with a kP, kI, kD, PIDSource, and PIDOuput
		m_StrafeController->SetInputRange(-180.0f, 180.0f); //sets input range to an angle
		m_StrafeController->SetOutputRange(-1.0, 1.0); //sets output range to a motor power
		m_StrafeController->SetAbsoluteTolerance(2.0f); //makes it so the robot ends at most 2 degrees of its target angle
		m_StrafeController->SetSetpoint(m_Target.x + Robot::navx.get()->GetYaw()); //sets target angle
		m_StrafeController->SetContinuous(true);
		m_StrafeController->Enable();

		DriverStation::ReportError("Starting DriveToOffset");
	}
	
	void DriveToOffset::Execute() {
		m_Position.z = Robot::navx.get()->GetYaw();
		if (m_Status == VisionStatus::ROTATE) {
			frc::DriverStation::ReportError("Current angle: " + std::to_string(m_Position.z));

			Robot::driveTrain->CartesianDrive(0, 0, m_PIDOut, Robot::navx.get()->GetYaw());
			
			double error = GetDriveError().z;
			DriverStation::ReportError("Turn error: " + std::to_string(error));
			if (abs(error) < 2)
				m_Status = VisionStatus::STRAFE;
		} else if (m_Status == VisionStatus::STRAFE) {

			Robot::driveTrain->CartesianDrive(0, m_PIDOut, 0, 0);

			DriverStation::ReportError("Done with turn");
		}
	}

	bool DriveToOffset::IsFinished() {
		return m_Status == VisionStatus::APPROACH;
	}


	void DriveToOffset::End() {

	}

	void DriveToOffset::Interrupted() {

	}

	void DriveToOffset::PIDWrite(double output) {
		m_PIDOut = output;
	}

}

