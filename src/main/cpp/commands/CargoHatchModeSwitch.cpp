/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CargoHatchModeSwitch.h"
#include "commands/LambdaCommand.h"
#include "Robot.h"
#include "OI.h"

namespace frc2019{

CargoHatchModeSwitch::CargoHatchModeSwitch(bool state) {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
  
  //if (OI::buttonBoard.GetRawButton(1)) {
  	AddSequential(new StopVacuum());
  	AddSequential(new frc::WaitCommand(2));
  //}
  
  AddSequential(new SetServo(state ? 0.0 : 0.65));
  AddSequential(new frc::WaitCommand(1));
  AddSequential(new LambdaCommand([]() {
	if(OI::buttonBoard.GetRawButton(1)){
		Robot::vacuum->Suck();
	}
	else {
		Robot::vacuum->Stop();
	}
  }));

}
}