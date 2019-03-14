/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LambdaCommand.h"

LambdaCommand::LambdaCommand(std::function<void()> func) : m_func(func) {}

void LambdaCommand::Initialize() {
	m_func();
}

void LambdaCommand::Execute() {}

bool LambdaCommand::IsFinished() { return true; }

void LambdaCommand::End() {}

void LambdaCommand::Interrupted() {}
