/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
#include <subsystems/DriveTrain.h>
#include "AHRS.h"
#include "OI.h"

//eayfughiafewef rg eaifghwife

namespace frc2019 {

class Robot : public frc::TimedRobot {
	public:
	void RobotInit() override;

	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	void TeleopInit() override;
	void TeleopPeriodic() override;

	void TestInit() override;
	void TestPeriodic() override;
	std::unique_ptr<Command> autonomousCommand;
	static std::shared_ptr<DriveTrain> driveTrain;
	static AHRS* navx;
	static std::shared_ptr<OI> oi;
};


}//frc2019