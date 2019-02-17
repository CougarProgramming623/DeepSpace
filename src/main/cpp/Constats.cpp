
#include <math.h>
#include "RobotConstants.h"
#include <wpi/ArrayRef.h>

namespace ohs623 {

double ReduceValue(double original, double exponent) {
	double result = pow(abs(original), exponent);// Result will always be positive because of abs()
	if (original < 0.0) {//Handle the case where it was originaly negitive
		result = -result;
	}
	return result;
}

void Normalize(wpi::MutableArrayRef<double> wheelSpeeds) {
  double maxMagnitude = std::abs(wheelSpeeds[0]);
  for (size_t i = 1; i < wheelSpeeds.size(); i++) {
    double temp = std::abs(wheelSpeeds[i]);
    if (maxMagnitude < temp) {
      maxMagnitude = temp;
    }
  }
  if (maxMagnitude > kMAX_VELOCITY) {
    for (size_t i = 0; i < wheelSpeeds.size(); i++) {
      wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
    }
  }
}


}//namespace
