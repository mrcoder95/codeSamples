/**

	Program: 				A 99 line topology optimization code written in MATLAB
	Developed by: 	Ole Sigmund
	Language:				MATLAB
	Source:					https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

		This program is converted to C++.

	Created by:		Mohamed Imran Peer Mohamed
	Language:		  C++
	Email:				mrmdimran95@gmail.com

	Purpose:		Learning

*/

#include "main.h"

int main (int argc, char* argv[]) {

	unsigned int nelx = 0;
	unsigned int nely = 0;
	double volfrac = 0.0;
	double penal = 0.0;
	double rmin = 0.0;
	double E = 0.0;
	{
		// Process command line Arguments
		for (int k = 1; k < argc; k++)
		{
			if (argv[k] == std::string("-x"))
			{
				nelx = std::atoi(argv[k + 1]);
				k++;
			}
			else if (argv[k] == std::string("-y"))
			{
				nely = std::atoi(argv[k + 1]);
				k++;
			}
			else if (argv[k] == std::string("-v"))
			{
				volfrac = std::atof(argv[k + 1]);
				k++;
			}
			else if (argv[k] == std::string("-p"))
			{
				penal = std::atof(argv[k + 1]);
				k++;
			}
			else if (argv[k] == std::string("-r"))
			{
				rmin = std::atof(argv[k + 1]);
				k++;
			}
			else if (argv[k] == std::string("-e"))
			{
				E = std::atof(argv[k + 1]);
				k++;
			}
		}
	}
	// If command line arguments not provided
	{
		if (nelx == 0) {
			cout << "Enter the Number of Rows = " ;
			cin >> nelx ;
		}
		if (nely == 0) {
			cout << "Enter the Number of Columns = " ;
			cin >> nely ;
		}
		if (volfrac == 0.0) {
			cout << "Enter the Number of Volfrac = " ;
			cin >> volfrac ;
		}
		if (penal == 0.0) {
			cout << "Enter the Number of Penal = " ;
			cin >> penal ;
		}
		if (rmin == 0.0) {
			cout << "Enter the Number of Rmin = " ;
			cin >> rmin ;
		}
		if (E == 0.0) {
			cout << "Enter the Young's Modulus = " ;
			cin >> E ;
		}
	}
	LineToplogy handle(nelx, nely, volfrac, penal, rmin, E);

	vector <vector <double>> x(handle.nelemY, vector <double> (handle.nelemX, handle.volfrac));
	vector <vector <double>> x_old;

	unsigned int iteration = 0;

	double residumm = 1.0;

	double tolerance = 1e-2;
	double c = 0.0;
	double sum = 0.0;

	unsigned int n1 = 0;
	unsigned int n2 = 0;

	while (residumm > tolerance)
	{

		iteration++;
		x_old = x;

		handle.FEA(x);

		c = 0.0;

		for (unsigned int j = 0; j < handle.nelemY; j++) {
			for (unsigned int i = 0; i < handle.nelemX; i++) {

				n1 = (handle.nelemY + 1) * (i    ) + j + 1;
				n2 = (handle.nelemY + 1) * (i + 1) + j + 1;

				double Ue[8] = { handle.U[(2 * n1) - 2], handle.U[(2 * n1) - 1], handle.U[(2 * n2) - 2], handle.U[(2 * n2) - 1],
								 handle.U[ 2 * n2     ], handle.U[(2 * n2) + 1], handle.U[ 2 * n1     ], handle.U[(2 * n1) + 1]
							   };

				double val = VecT_Mat_Vec_Product (handle.KE, Ue);
				c += std::pow(x[j][i], handle.penal) * val;

				handle.DC[j][i] = -handle.penal * std::pow(x[j][i], handle.penal - 1) * val;
			}
		}

		handle.Mesh_Filter(x);

		handle.Opt_Crt_Update(x);

		residumm = std::abs(x[0][0] - x_old[0][0]);

		sum = 0.0;

		for (unsigned int i = 0; i <  x.size(); i++)
			for (unsigned int j = 0; j <  x[i].size(); j++) {
				if (std::abs(x[i][j] - x_old[i][j]) > residumm)
					residumm = std::abs(x[i][j] - x_old[i][j]);
				sum += x[i][j];
			}

		cout << "It.: " << iteration << " Obj.: " << c << " Vol.: " << sum /(handle.nelemX * handle.nelemY) << " ch.: " << residumm << endl ;
	}

	return 0;
}
