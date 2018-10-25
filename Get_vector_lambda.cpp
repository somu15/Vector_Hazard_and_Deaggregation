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

void vec_haz_comps(MatrixXd IM_info, MatrixXd Deagg1, MatrixXd Deagg2, MatrixXd Deaggmin, MatrixXd & output, double & vechaz){

// MatrixXd vec_haz_comps(MatrixXd IM_info, MatrixXd Deagg1, MatrixXd Deagg2, MatrixXd Deaggmin) {

	double IM1 = IM_info(0);
	double Haz1 = IM_info(1);
	double IM2 = IM_info(2);
	double Haz2 = IM_info(3);
	double tot_haz = IM_info(4);
	double corr = IM_info(5);
	int NM = IM_info(6);
	int NR = IM_info(7);
	double prob1, prob2, joint_prob, joint_prob_ex;
//	MatrixXd output(NM,NR);

	vechaz = 0;

	for (int i = 0; i <= NM - 1; ++i)
	{
		for (int j = 0; j <= NR - 1; ++j)
		{
			if (Deaggmin(i, j) <= 0) {
				output(i, j) = 0;
			}
			else {
				prob1 = 1 - (Deagg1(i, j)*Haz1) / (Deaggmin(i, j)*tot_haz);
				prob2 = 1 - (Deagg2(i, j)*Haz2) / (Deaggmin(i, j)*tot_haz);
				joint_prob = Gaussian_Copula(prob1, prob2, corr);
				joint_prob_ex = 1 - prob1 - prob2 + joint_prob;
				output(i, j) = joint_prob_ex*Deaggmin(i, j);
			}

			if (output(i, j) != output(i, j)) { 
				output(i, j) = 0;
			}

			vechaz = vechaz + output(i, j);
		}
	}

	//return output;

}