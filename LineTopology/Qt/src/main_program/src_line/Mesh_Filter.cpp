/**
    Mesh Filter

    Original Code was developed by Ole Sigmund in MATLAB.
    Source: https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

    The MATLAB code is converted to C++ code.
    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "../main.h"

void LineToplogy::Mesh_Filter (std::vector <std::vector <double>> &x)
{
	DCN.resize(nelemY, std::vector <double> (nelemX, 0.0));
	double sum = 0.0;
	double fac = 0.0;
	unsigned int Min1 = 0;
	unsigned int Min2 = 0;
	for(int i = 0 ; i < nelemX ; i++)
	{
		for(int j = 0 ; j < nelemY ; j++)
		{
			sum = 0.0 ;
			Min1 = mini(i + std::floor(rmin), nelemX - 1);
			for(int k = maxi(i - std::floor(rmin), 0); k <= Min1; k++)
			{
                Min2 = mini(j + std::floor(rmin), nelemY - 1);
				for (int l = maxi(j - std::floor(rmin), 0); l <= Min2; l++)
				{
                    fac = rmin - std::sqrt(std::pow(i - k, 2) + std::pow(j - l, 2));
					sum += maxi(0, fac) ;
					DCN[j][i] += maxi(0, fac) * x[l][k] * DC[l][k];
				}
			}
			DCN[j][i] /= (x[j][i] * sum);
		}
	}
}
