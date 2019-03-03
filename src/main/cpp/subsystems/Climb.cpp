#include "subsystems/Climb.h"
#include "RobotConstants.h"
#include "GameEnums.h"
#include "Cob.h"
#include "commands/StopClimb.h"

namespace frc2019 {

//Weather or not we hit the hard limit while climbing (true when we climb to the top)
Climb::Climb() : frc::Subsystem("Climb"), m_ClimbMotor(CLIMB_ID) {

}

void Climb::InitDefaultCommand() {
    
}

}//namespace