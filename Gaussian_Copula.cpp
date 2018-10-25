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
#include "Functions.h"

double Gaussian_Copula(double prob1, double prob2, double corr) {

	MatrixXd corr_mat(2, 2);
	corr_mat(0, 0) = 1;
	corr_mat(0, 1) = corr;
	corr_mat(1, 0) = corr;
	corr_mat(1, 1) = 1;

	double inv_prob1 = NormalCDFInverse(prob1);
	double inv_prob2 = NormalCDFInverse(prob2);

	MatrixXd mu(1, 2);
	mu(0, 0) = inv_prob1;
	mu(0, 1) = inv_prob2;
	double tol = 1e-5, arb = 2.5;
	int matsize = 2, Nmax = 10000;
	MatrixXd outs = MVNCDF(mu, corr_mat, tol, arb, matsize, Nmax);
	return outs(0,0);

}