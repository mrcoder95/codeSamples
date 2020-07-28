/**
    Optimum Criteria Update

    Original Code was developed by Ole Sigmund in MATLAB.
    Source: https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

    The MATLAB code is converted to C++ code.
    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/
#include "../main.h"

void LineToplogy::Opt_Crt_Update (std::vector <std::vector <double>> &x)
{

	double l1 = 0;
	double l2 = 100000;
	double move = 0.2;
	double lmid = 0.0;
	double sum = 0.0;

	std::vector <std::vector <double>> x_new(x.size(), std::vector <double> (x[0].size(), 0.0));

	while((l2 - l1) > 1e-4)
	{
		lmid = 0.5 * (l2 + l1);
		sum = 0.0;
			
		for (unsigned int i = 0; i <  x.size(); i++)
			for (unsigned int j = 0; j <  x[i].size(); j++) {
				x_new[i][j] = maxi(0.001, maxi(x[i][j] - move, mini(1., mini(x[i][j] + move, x[i][j] * std::sqrt(- DCN[i][j] / lmid)))));
				sum += x_new[i][j];
			}
		if ((sum - (volfrac * nelemX * nelemY)) > 0)
			l1 = lmid ;
		else
			l2 = lmid ;
		
	}
	
	x = x_new;
	
	DCN.clear();
}
