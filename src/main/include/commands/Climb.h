/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>

#include "GameEnums.h"


namespace frc2019 {

class Climb : public frc::CommandGroup {
public:
	Climb(ClimbHeight height);
private:
	ClimbHeight m_Height;
};


}//namespace