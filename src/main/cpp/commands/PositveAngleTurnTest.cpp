/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositveAngleTurnTest.h"
#include "Robot.h"
#include "commands/Turn.h"
#include "Constants.h"

namespace frc2019 {
PositveAngleTurnTest::PositveAngleTurnTest() : frc::CommandGroup("Turn Test") {
  using namespace ohs623; //since WAIT(x) is found under the ohs623 namespace in Constants.h

  //turn 180 degrees clockwise in 45 degree increments
  for(int i = 0; i < 4; i++) {
    AddSequential(new Turn(i * 45.0f));
    WAIT(0.5);
  }

  AddSequential(new Turn(0.0f));
  WAIT(0.5);

  //turn 180 degrees counter-clockwise in 45 degree increments
  for(int i = 0; i < 4; i++) {
    AddSequential(new Turn(-1 * i * 45.0f));
    WAIT(0.5);
  }
  AddSequential(new Turn(0.0f));
}
} //namespace
