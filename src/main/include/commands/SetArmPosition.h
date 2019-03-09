/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "RobotConstants.h"
#include "GameEnums.h"

namespace frc2019 {

class SetArmPosition : public frc::Command {
public:
	SetArmPosition(int);
	SetArmPosition(DialPosition);

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
 private:
	int m_setpoint;
	DialPosition m_dialPosition;
};


}