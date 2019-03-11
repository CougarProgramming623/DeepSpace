/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>


namespace frc2019 {
/* 
 * This command runs the climb motor backwards in order to either bring the prg leg back up (if we climbed all the way), 
 * or to bring the peg legs back down if we climbed early and the peg legs didnt buckle
 */
class ClimbDown : public frc::Command {

public:
	ClimbDown();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	frc::Timer m_Timer;// Counts how long we've been climbing down for
	double m_LastTime = -1.0;//The value from the timer from the last call to Execute() (used for finding delta time)
};


}//namespace
