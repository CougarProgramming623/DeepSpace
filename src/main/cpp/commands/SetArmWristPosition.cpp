/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetArmWristPosition.h"
#include "commands/SetArmPosition.h"
#include "commands/SetWristPosition.h"
#include "Robot.h"

namespace frc2019 {
	SetArmWristPosition::SetArmWristPosition(DialPosition position) {
		Requires(Robot::arm.get());
		Requires(Robot::wrist.get());

		AddParallel(new SetArmPosition(position));
		AddSequential(new SetWristPosition(position));
			
	}
}
