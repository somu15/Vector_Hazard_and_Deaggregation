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
using Eigen::MatrixXd;
#include "Functions.h"

int main()
{
	//**********INTRODUCTION**********
	cout << "VECTOR PSHA USING SALIENT FEATURES OF DEAGGREGATION MATRICES (version 1.0)" << endl << "Written by Somayajulu Dhulipala (email: somdhulipala9@gmail.com)" << endl << "from Dhulipala, Rodriguez-Marek, and Flint (2018) Computation of Vector Hazard Using Salient Features of Seismic Hazard Deaggregation" << endl << endl << endl;



	//**********USER INPUTS**********
	// USER INPUTS IM AND OTHER INFORMATION THROUGH A TEXT FILE
	char filename[5000], filename1[5000], filename2[5000], filename3[5000];
	cout << "INPUT1: The path of a text file containing the following information in the same order. You should substitute numerical values in place of the text shown below. For help refer to the IM_and_other_info.txt supplied with this program." << endl << endl;
	cout << "Magnitude of Intensity Measure 1" << endl << "Hazard corresponding to IM1 level" << endl << "Magnitude of Intensity Measure 2" << endl << "Hazard corresponding to IM2 level" << endl << "Total hazard" << endl << "Pearson correlation between IM1 and IM2" << endl << "Number of magnitude bins in a deaggregation matrix" << endl << "Number of distance bins in a deaggregation matrix"<< endl << endl << endl;
	cin >> filename;
	// char filename[500] = "C:/Users/lakshd5/Desktop/IM_info.txt";
	MatrixXd IM_info = Matrix_from_TXT_Som(filename, 8, 1);
	cout << endl << endl;
	int NM = IM_info(6);
	int NR = IM_info(7);

	// USER INPUTS DEAGGREGATION MATRIX FOR IM1 THROUGH A TEXT FILE
	cout << "INPUT2: The path of a text file containing the deaggregation matrix corresponding to IM1 level. The input matrix should have magnitude bins as its rows and distance bins as its columns. For help refer to the Deagg_IM1.txt supplied with this program." << endl << endl;
	// char filename1[500] = "C:/Users/lakshd5/Desktop/Deagg1.txt";
	cin >> filename1;
	MatrixXd Deagg1 = Matrix_from_TXT_Som(filename1, NM, NR);
	cout << endl << endl;

	// USER INPUTS DEAGGREGATION MATRIX FOR IM2 THROUGH A TEXT FILE
	cout << "INPUT3: The path of a text file containing the deaggregation matrix corresponding to IM2 level. The input matrix should have magnitude bins as its rows and distance bins as its columns. For help refer to the Deagg_IM2.txt supplied with this program." << endl << endl;
	// char filename2[500] = "C:/Users/lakshd5/Desktop/Deagg2.txt";
	cin >> filename2;
	MatrixXd Deagg2 = Matrix_from_TXT_Som(filename2, NM, NR);
	cout << endl << endl;
	
	// USER INPUTS DEAGGREGATION MATRIX FOR A MINIMUM IM LEVEL THROUGH A TEXT FILE
	cout << "INPUT4: The path of a text file containing the deaggregation matrix corresponding to a low IM level. The input matrix should have magnitude bins as its rows and distance bins as its columns. For help refer to the Deagg_min.txt supplied with this program." << endl << endl;
	// char filename3[500] = "C:/Users/lakshd5/Desktop/Deaggmin.txt";
	cin >> filename3;
	MatrixXd Deaggmin = Matrix_from_TXT_Som(filename3, NM, NR);
	cout << endl << endl;

	MatrixXd vecDeagg(NM, NR);
	double vechaz = 0;

	vec_haz_comps(IM_info, Deagg1, Deagg2, Deaggmin, vecDeagg, vechaz);

	// vecDeagg = vec_haz_comps(IM_info, Deagg1, Deagg2, Deaggmin);

	cout << "The vector hazard is:" << endl << vechaz << endl << endl << endl;
	system("pause");

	/* cout << "The vector deaggregation is:" << endl << vecDeagg << endl << endl << endl;
	system("pause");*/

}

/*int main()
{
	int rows = 600, cols = 5;
	char text[500] = "C:/Users/lakshd5/Dropbox/GM scaling/Northridge_Saticoy_Comp.090.txt";
	MatrixXd req_mat = Matrix_from_TXT_Som(text, rows, cols);
	cout << "MVNCDF is " << endl << req_mat << endl;
	system("pause");
	return 0;
}*/


/*int main()
{
	MatrixXd b(1,4), SIG(4,4);
	double tol = 1e-16, arb = 2.5;
	int matsize = 4, Nmax = 10000;
	b(0, 0) = -5; b(0, 1) = 1; b(0, 2) = 4; b(0, 3) = 0;
	SIG(0, 0) = 1; SIG(0, 1) = 0.2; SIG(0, 2) = 0.5; SIG(0, 3) = 0.7;
	SIG(1, 0) = 0.2; SIG(1, 1) = 1; SIG(1, 2) = 0.5; SIG(1, 3) = 0.35;
	SIG(2, 0) = 0.5; SIG(2, 1) = 0.5; SIG(2, 2) = 1; SIG(2, 3) = 0.85;
	SIG(3, 0) = 0.7; SIG(3, 1) = 0.35; SIG(3, 2) = 0.85; SIG(3, 3) = 1;
	MatrixXd VARS = MVNCDF(b, SIG, tol, arb, matsize, Nmax);
	cout << "MVNCDF is " << endl << VARS(0, 0) << endl << "Error is " << endl << VARS(0, 1) << endl << "Iterations are " << endl << VARS(0, 2) << endl;
	system("pause");
	return 0;
}*/

/* 

b(0, 0) = -5; b(0, 1) = 1; b(0, 2) = 4; b(0, 3) = 0;
SIG(0, 0) = 1; SIG(0, 1) = 0.2; SIG(0, 2) = 0.5; SIG(0, 3) = 0.7;
SIG(1, 0) = 0.2; SIG(1, 1) = 1; SIG(1, 2) = 0.5; SIG(1, 3) = 0.35;
SIG(2, 0) = 0.5; SIG(2, 1) = 0.5; SIG(2, 2) = 1; SIG(2, 3) = 0.85;
SIG(3, 0) = 0.7; SIG(3, 1) = 0.35; SIG(3, 2) = 0.85; SIG(3, 3) = 1;

*/
