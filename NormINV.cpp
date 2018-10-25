#include "stdafx.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

/*double NormalCDFInverse(double p);
double RationalApproximation(double t);*/

double RationalApproximation(double t)
{
	// Abramowitz and Stegun formula 26.2.23.
	// The absolute value of the error should be less than 4.5 e-4.
	double c[] = { 2.515517, 0.802853, 0.010328 };
	double d[] = { 1.432788, 0.189269, 0.001308 };
	return t - ((c[2] * t + c[1])*t + c[0]) /
		(((d[2] * t + d[1])*t + d[0])*t + 1.0);
}

double NormalCDFInverse(double p)
{
	/*if (p < 0.0 || p > 1.0)
	{
		std::stringstream os;
		os << "Invalid input argument (" << p
			<< "); must be larger than 0 but less than 1.";
		throw std::invalid_argument(os.str());
	}*/

	if (p <= 0)
	{
		return std::numeric_limits<int>::min();
	}
	else if (p >= 1)
	{
		return std::numeric_limits<int>::max();
	}
	else if (p < 0.5 && p!= 0)
	{
		return -RationalApproximation(sqrt(-2.0*log(p)));
	}
	else
	{
		return RationalApproximation(sqrt(-2.0*log(1 - p)));
	}


	// See article above for explanation of this section.
	/*if (p < 0.5)
	{
		// F^-1(p) = - G^-1(p)
		return -RationalApproximation(sqrt(-2.0*log(p)));
	}
	else
	{
		// F^-1(p) = G^-1(1-p)
		return RationalApproximation(sqrt(-2.0*log(1 - p)));
	}*/
}