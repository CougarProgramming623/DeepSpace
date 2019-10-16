

const double FOOT = 12.0;
const double SQRT_2 = 1.41421356237;
const double PI = 3.14159265359;

#include <wpi/ArrayRef.h>

namespace ohs623 {

/**
 * Computes origional to the exponent, and keeps the sign the same
 */
double ReduceValue(double original, double exponent);
//Waits the specified number of seconds
//Can only be used in a CommandGroup class since it requires AddSequential
#define WAIT(x) AddSequential(new frc::WaitCommand(x))

}//frc2019
