/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BooleanToggle.h"

namespace frc2019 {
BooleanToggle::BooleanToggle(bool* ptr, std::function<void(bool newValue)> onFlip) : boolean(ptr), onFlip(onFlip) {

}

void BooleanToggle::Initialize() {
	if(*boolean) {
		*boolean = false;
	} else {
		*boolean = true;
	}
	onFlip(*boolean);
}

void BooleanToggle::Execute() {

}

bool BooleanToggle::IsFinished() { return true; }

void BooleanToggle::End() {

}

void BooleanToggle::Interrupted() {

}
}//namespace