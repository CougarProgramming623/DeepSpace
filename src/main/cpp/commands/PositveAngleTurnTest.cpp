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
  using namespace ohs623;
  AddSequential(new Turn(45.0f));
  WAIT(0.5);
  AddSequential(new Turn(90.0f));
  WAIT(0.5);
  AddSequential(new Turn(135.0f));
  WAIT(0.5);
  AddSequential(new Turn(180.0));
  WAIT(0.5);
  AddSequential(new Turn(0.0f));
  WAIT(0.5);
  AddSequential(new Turn(-45.0f));    
  WAIT(0.5);
  AddSequential(new Turn(-90.0f));
  WAIT(0.5);
  AddSequential(new Turn(-135.0f));
  WAIT(0.5);
  AddSequential(new Turn(-180.f));  
  WAIT(0.5);
  AddSequential(new Turn(0.0f));
  //Requires(Robot::driveTrain.get());
  //Robot::navx.get()->ZeroYaw();
}
}
