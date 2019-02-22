#pragma once

#include <ctre/Phoenix.h>
#include "GameEnums.h"

namespace talon {
    int GetTalonData(TalonSRX* talonMC, TalonData data);
    void ConfigurePotentiometer(TalonSRX* talonMC, double kP, double kI, double kD);
}