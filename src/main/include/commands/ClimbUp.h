/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>
#include <frc/WPILib.h>


#include "GameEnums.h"


namespace frc2019 {

/*
 * Runs the climb motor forward so that the peg legs deploy
 */
class ClimbUp : public frc::Command {
public:
	ClimbUp();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	frc::Timer m_Timer;
};


}//namespace
