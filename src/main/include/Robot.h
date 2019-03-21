/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
#include "subsystems/DriveTrain.h"
#include "subsystems/Arm.h"
#include "subsystems/HatchPickup.h"
#include "subsystems/Vacuum.h"
#include "subsystems/Wrist.h"
#include "subsystems/HatchPickup.h"
#include "subsystems/Climb.h"
#include "AHRS.h"
#include "OI.h"

namespace frc2019 {

class Robot : public frc::TimedRobot {
public: //methods
	void RobotInit() override;
	void RobotPeriodic() override;

	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	void TeleopInit() override;
	void TeleopPeriodic() override;

	void DisabledInit() override;
	
	void TestInit() override;
	void TestPeriodic() override;

public: //pointers
	std::unique_ptr<Command> autonomousCommand;
	static std::shared_ptr<DriveTrain> driveTrain;
	static std::shared_ptr<Arm> arm;
	static std::shared_ptr<HatchPickup> fork;
	static std::shared_ptr<AHRS> navx;
	static std::shared_ptr<OI> oi;
	static std::shared_ptr<Vacuum> vacuum;
	static std::shared_ptr<Climb> climb;
	static std::shared_ptr<Wrist> wrist;
private:
	bool isTeleop = false;

};
}//frc2019