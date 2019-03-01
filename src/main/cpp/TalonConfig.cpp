#include "TalonConfig.h"

#define kPID_LOOP_IDX 0
#define kTIMEOUT_MS 30

using namespace frc2019;
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

void ConfigurePotentiometer(TalonSRX* talonMC, double kP, double kI, double kD) {
    talonMC->SetSelectedSensorPosition(talonMC->GetSelectedSensorPosition());
    talonMC->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, kTIMEOUT_MS);
    talonMC->ConfigNominalOutputForward(0, kTIMEOUT_MS);
	talonMC->ConfigNominalOutputReverse(0, kTIMEOUT_MS);
	talonMC->ConfigPeakOutputForward(1.0, kTIMEOUT_MS);		
    talonMC->ConfigPeakOutputReverse(-1.0, kTIMEOUT_MS);
    talonMC->Config_kF(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);
    talonMC->Config_kP(kPID_LOOP_IDX, kP, kTIMEOUT_MS);
    talonMC->Config_kI(kPID_LOOP_IDX, kI, kTIMEOUT_MS);
    talonMC->Config_kD(kPID_LOOP_IDX, kD, kTIMEOUT_MS);
}
}