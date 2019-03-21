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
	AddSequential(new StopVacuum());
	AddSequential(new VacuumWait());
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