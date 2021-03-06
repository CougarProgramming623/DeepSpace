/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/DriverStation.h>
#include <functional>

namespace frc2019 {

class BooleanToggle : public frc::Command {
public:
	BooleanToggle(bool* boolean, std::function<void(bool newValue)> onFlip);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
 private:
	bool* boolean;
	std::function<void(bool newValue)> onFlip;
};
}//frc2019