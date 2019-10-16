#include "PID.h"

namespace ohs623 {

double OHSPIDController::PIDGet() {
	return m_Input;
}

void OHSPIDController::PIDWrite(double output) {
	m_Output = output;
}


}