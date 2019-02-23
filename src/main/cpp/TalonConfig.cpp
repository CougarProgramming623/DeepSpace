#include "TalonConfig.h"

#define kPID_LOOP_IDX 0
#define kTIMEOUT_MS 30

namespace talon {
int GetTalonData(TalonSRX* talonMC, TalonData data){
    //based on the value of the data parameter, the corresponding data value is returned
    switch(data){
        case TalonData::SENSOR_POSITION:
            return talonMC->GetSelectedSensorPosition(); //encoder or potentiometer reading
        case TalonData::SENSOR_VELOCITY:
            return talonMC->GetSelectedSensorVelocity(); //encoder or potentiometer velocity
        case TalonData::TARGET:
            return talonMC->GetClosedLoopTarget(); //PID setpoint
        case TalonData::ERROR:
            return talonMC->GetClosedLoopError(); //PID error
        case TalonData::PERCENT_OUTPUT:
            return talonMC->GetMotorOutputPercent(); //motor output [-1.0, 1.0]
        default:
            return 0; //return 0 if random value
    };
} //GetTalonData()

void ConfigurePotentiometer(TalonSRX* talonMC, double kP, double kI, double kD) {
    //configures a potentiometer on the designmated TalonSRX
    //talonMC->SetSelectedSensorPosition(talonMC->GetSelectedSensorPosition());
    talonMC->SetSelectedSensorPosition(0); //set the position as 0
    talonMC->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, kTIMEOUT_MS); //configure FeedbackDevice as Analog
    talonMC->ConfigNominalOutputForward(0, kTIMEOUT_MS);
	talonMC->ConfigNominalOutputReverse(0, kTIMEOUT_MS);
	talonMC->ConfigPeakOutputForward(0.25, kTIMEOUT_MS); //configure the peak output forward	
    talonMC->ConfigPeakOutputReverse(-0.35, kTIMEOUT_MS); //configure the peak output reverse
    //configure P I D values for the potentiometer
    talonMC->Config_kF(kPID_LOOP_IDX, 0.0, kTIMEOUT_MS);
    talonMC->Config_kP(kPID_LOOP_IDX, kP, kTIMEOUT_MS);
    talonMC->Config_kI(kPID_LOOP_IDX, kI, kTIMEOUT_MS);
    talonMC->Config_kD(kPID_LOOP_IDX, kD, kTIMEOUT_MS);
} //ConfigurePotentiometer()
} //talon