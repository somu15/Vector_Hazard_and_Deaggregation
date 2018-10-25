#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
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

MatrixXd Matrix_from_TXT_Som(char filename[500], int rows, int cols) {

	MatrixXd req_mat(rows, cols);

	ifstream file_(filename);

	if (file_.is_open()) {

		for (int i = 0; i <= rows-1; ++i)
		{
			for (int j = 0; j <= cols - 1; ++j)
			{
				file_ >> req_mat(i,j);
			}
		}

		file_.close();

	}
	else
		std::cout << "file is not open" << '\n';

	std::cin.get();
	return req_mat;
}
