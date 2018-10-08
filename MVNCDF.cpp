#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <math.h>
#include "C:\Users\lakshd5\Dropbox\C++ libraries\Stats lib\include\stats.hpp"
#include "C:\Users\lakshd5\Dropbox\C++ libraries\eigen-eigen-b3f3d4950030\Eigen\Dense"
#include "C:\Users\lakshd5\Dropbox\C++ libraries\eigen-eigen-b3f3d4950030\Eigen\Cholesky"
using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;

double NormalCDFInverse(double p);

MatrixXd MVNCDF(MatrixXd b, MatrixXd SIG, double tol, double arb, int matsize, int Nmax)
{


	MatrixXd C = SIG.llt().matrixL();
	double intsum = 0;
	double varsum = 0;
	double d = 0;
	double delta;
	MatrixXd y(1, matsize);
	MatrixXd f(1, matsize);
	MatrixXd e(1, matsize);
	e(0,0) = stats::pnorm(b(0, 0) / C(0, 0), 0, 1);
	f(0,0) = e(0, 0);
	double error = 1000;
	int iter = 1;
	// stats::rlogis(<location parameter>,<scale parameter>,<seed value or random number engine>);
	while (error >= tol && iter<Nmax)
	{
		for (int i = 1; i <= matsize-1; i = i + 1)
		{
			double temp = stats::runif(0, 1)*(e(0,i-1) - d);
			y(0, i - 1) = NormalCDFInverse(d + temp);
			double cY = 0;
			for (int j = 0; j <= i - 1; j = j + 1)
			{
				cY = cY + C(i, j)*y(0, j);
			}
			e(0, i) = stats::pnorm((b(0, i)-cY)/C(i,i), 0, 1);
			f(0, i) = (e(0, i) - d)*f(0, i - 1);
		}
		iter = iter + 1;
		delta = (f(0, matsize - 1) - intsum) / iter;
		intsum = intsum + delta;
		varsum = (iter - 2)*varsum / iter + pow(delta, 2);
		error = arb*pow(varsum, 0.5);
	}
	MatrixXd VARS(1, 3);
	VARS(0, 0) = intsum;
	VARS(0, 1) = error;
	VARS(0, 2) = iter;
	return VARS;
}
