#pragma once

#include <frc/PIDController.h>
#include <frc/PIDSource.h>
#include <frc/PIDOutput.h>

namespace ohs623 {

//Represents all parts of a PID Loop in one class
//A PIDController is a PIDOutput
class OHSPIDController : public frc::PIDController, frc::PIDSource {
public:

	inline OHSPIDController(double p, double i, double d, double period = 0.05)
		: PIDController(p, i, d, this, this, period) {}

	inline OHSPIDController(double p, double i, double d, double outputMin, double outputMax, double period = 0.05)
		: OHSPIDController(p, i, d, period) {
		SetOutputRange(outputMin, outputMax);
	}
	
	//Needed by WPILIB
	virtual double PIDGet();
	virtual void PIDWrite(double output);

	inline void SetInput(double input) { m_Input = input; }
	inline double GetInput() { return m_Input; }
	inline double GetOutput() { return m_Output; }

private:
	double m_Input, m_Output;

};
}