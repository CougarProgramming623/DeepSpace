
#include <math.h>

double ReduceValue(double origional, double exponent) {
	bool flip = origional < 0;
	origional = pow(abs(origional), exponent);
	if (flip) {
		origional = -origional;
	}
	return origional;
}
