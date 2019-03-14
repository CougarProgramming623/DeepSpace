/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetArmWristPositionSecure.h"
#include "commands/SetArmPosition.h"
#include "commands/SetWristPosition.h"
#include "Robot.h"
#include "commands/WristWait.h"

namespace frc2019 {
	SetArmWristPositionSecure::SetArmWristPositionSecure(DialPosition position) {
		Requires(Robot::arm.get());
		Requires(Robot::wrist.get());
		
		AddSequential(new SetWristPosition(position));
		AddSequential(new WristWait());
		AddSequential(new SetArmPosition(position));
	}
}
