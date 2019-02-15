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

template<typename T>

class VariableSet : public frc::Command {
public:
	VariableSet(T* variable, T value, std::function<void(T newValue)> onSet) : variable(variable), value(value), onSet(onSet) {}
	void Initialize() {
		*variable = value;
		onSet(value);
	}
	
	void Execute() {}
	bool IsFinished() {}
	void End() {}
	void Interrupted() {}

 private:
	T value;
	T* variable;
	std::function<void(T newValue)> onSet;
};

}//namespace