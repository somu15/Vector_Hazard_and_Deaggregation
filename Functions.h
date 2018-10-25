#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
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

MatrixXd MVNCDF(MatrixXd b, MatrixXd SIG, double tol, double arb, int matsize, int Nmax);

MatrixXd Matrix_from_TXT_Som(char filename[500], int rows, int cols);

// MatrixXd vec_haz_comps(MatrixXd IM_info, MatrixXd Deagg1, MatrixXd Deagg2, MatrixXd Deaggmin);

void vec_haz_comps(MatrixXd IM_info, MatrixXd Deagg1, MatrixXd Deagg2, MatrixXd Deaggmin, MatrixXd & output, double & vechaz);

double Gaussian_Copula(double prob1, double prob2, double corr);

#endif#pragma once
