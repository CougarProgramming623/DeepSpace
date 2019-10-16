
#include "commands/DriveToOffset.h"
#include "Constants.h"
#include <frc/DriverStation.h>
#include "Vec.h"
#include "Robot.h"
#include "Cob.h"
#include "CobConstants.h"

namespace frc2019 {

	void DriveToOffset::Initialize() {
		double p = Cob::GetValue<double>(COB_DRIVE_P);
		double i = Cob::GetValue<double>(COB_DRIVE_I);
		double d = Cob::GetValue<double>(COB_DRIVE_D);

		if (p == -1 || i == -1 || d == -1) {
			DriverStation::ReportError("Unable to find all PID values! Make sure /cob/drive/* are defined!");
		} else {
			m_Controller.reset(new OHSPIDController(p, i, d, 0.0, 1.0));
		}
		//Robot::driveTrain->CartesianDrive();
	}
	
	void DriveToOffset::Execute() {
		//Robot::driveTrain->ConfigureEncoders()

		double power = m_Controller->GetOutput();
		frc::DriverStation::ReportError("DTO power x: " + std::to_string(x) + ", y: " + std::to_string(y) + ", z: " + std::to_string(z));
		Robot::driveTrain->CartesianDrive(x, y, 0, z);
	}

	bool DriveToOffset::IsFinished() {
		Vec3 error = (m_Target - m_Position);
		frc::DriverStation::ReportError("DTO: error " + std::to_string(error.Length()) + "ft " + std::to_string(error));
		return error.Length() < (4 / FOOT);//Stop when the error is less than 4 inches
	}


	void DriveToOffset::End() {

	}

	void DriveToOffset::Interrupted() {

	}


}

