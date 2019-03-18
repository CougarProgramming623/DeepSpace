/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>
#include <frc/WPILib.h>
#include "commands/StopVacuum.h"
#include "commands/TurnOnVacuum.h"
#include "commands/SetServo.h"

namespace frc2019{

class CargoHatchModeSwitch : public frc::CommandGroup {
 public:
  CargoHatchModeSwitch(bool);
};
}