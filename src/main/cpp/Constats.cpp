
#include <math.h>

namespace ohs623 {


double ReduceValue(double original, double exponent) {
	double result = pow(abs(original), exponent);// Result will always be positive because of abs()
	if (original < 0.0) {//Handle the case where it was originaly negitive
		result = -result;
	}
	return result;
}


}//namespace
