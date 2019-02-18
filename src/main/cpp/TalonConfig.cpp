#include "TalonConfig.h"

namespace talon {
    
    int GetTalonData(TalonSRX* talonMC, TalonData data){
        switch(data){
            case TalonData::SENSOR_POSITION:
                return talonMC->GetSelectedSensorPosition();
            case TalonData::SENSOR_VELOCITY:
                return talonMC->GetSelectedSensorVelocity();
            case TalonData::TARGET:
                return talonMC->GetClosedLoopTarget();
            case TalonData::ERROR:
                return talonMC->GetClosedLoopError();
            case TalonData::PERCENT_OUTPUT:
                return talonMC->GetMotorOutputPercent();
            default:
                return 0;
        };
    }

}