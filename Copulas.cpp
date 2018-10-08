// Copulas.cpp : Defines the entry point for the console application.
//

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

MatrixXd MVNCDF(MatrixXd b, MatrixXd SIG, double tol, double arb, int matsize, int Nmax);

using Eigen::MatrixXd;

int main()
{
	MatrixXd b(1,4), SIG(4,4);
	double tol = 1e-16, arb = 2.5;
	int matsize = 2, Nmax = 10000;
	b(0, 0) = -5; b(0, 1) = 1; b(0, 2) = 4; b(0, 3) = 0;
	SIG(0, 0) = 1; SIG(0, 1) = 0.2; SIG(0, 2) = 0.5; SIG(0, 3) = 0.7;
	SIG(1, 0) = 0.2; SIG(1, 1) = 1; SIG(1, 2) = 0.5; SIG(1, 3) = 0.35;
	SIG(2, 0) = 0.5; SIG(2, 1) = 0.5; SIG(2, 2) = 1; SIG(2, 3) = 0.85;
	SIG(3, 0) = 0.7; SIG(3, 1) = 0.35; SIG(3, 2) = 0.85; SIG(3, 3) = 1;
	MatrixXd VARS = MVNCDF(b, SIG, tol, arb, matsize, Nmax);
	cout << "MVNCDF is " << endl << VARS(0, 0) << endl << "Error is " << endl << VARS(0, 1) << endl << "Iterations are " << endl << VARS(0, 2) << endl;
	system("pause");
	return 0;
}

/* 

b(0, 0) = -5; b(0, 1) = 1; b(0, 2) = 4; b(0, 3) = 0;
SIG(0, 0) = 1; SIG(0, 1) = 0.2; SIG(0, 2) = 0.5; SIG(0, 3) = 0.7;
SIG(1, 0) = 0.2; SIG(1, 1) = 1; SIG(1, 2) = 0.5; SIG(1, 3) = 0.35;
SIG(2, 0) = 0.5; SIG(2, 1) = 0.5; SIG(2, 2) = 1; SIG(2, 3) = 0.85;
SIG(3, 0) = 0.7; SIG(3, 1) = 0.35; SIG(3, 2) = 0.85; SIG(3, 3) = 1;

*/
