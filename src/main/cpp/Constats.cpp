
#include <math.h>

namespace ohs623 {
double ReduceValue(double origional, double exponent) {
	double result = pow(abs(origional), exponent);// Result will always be positive because of abs()
	if (origional < 0.0) {//Handle the case where it was origionally negitive
		result = -result;
	}
	return result;
}
}//namespace