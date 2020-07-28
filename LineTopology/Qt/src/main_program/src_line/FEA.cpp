/**
    Finite Element Analysis
    Solving linear system of equation using GMRES solver (BOOST)

    Original Code was developed by Ole Sigmund in MATLAB.
    Source: https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

    The MATLAB code is converted to C++ code.
    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "../main.h"
#include "mat_operations.cpp"

void LineToplogy::FEA (std::vector <std::vector <double>> &x)
{
	
    // Global Stiffness Matrix Size
	unsigned int SIZE = 2 * (nelemX + 1) * (nelemY + 1);
	
	
    // Stiffness(Sparse) Matrix
	compressed_mat K(SIZE, SIZE, 100);
	
	// Vector
    Vector F(SIZE, 0.0);
	U.resize(SIZE, 0.0);
	
    // Building Stiffness Matrix
    #pragma omp parallel for
	for (unsigned int i = 0; i < nelemX; i++) {
        unsigned int n1 = 0;
        unsigned int n2 = 0;

        double val = 0.0;
		for (unsigned int j = 0; j < nelemY; j++) {
			
			n1 = (nelemY + 1) * (i    ) + j + 1;
			n2 = (nelemY + 1) * (i + 1) + j + 1;
			
			unsigned int dof[8] = { (2 * n1) - 2, (2 * n1) - 1, (2 * n2) - 2, (2 * n2) - 1, 
									 2 * n2     , (2 * n2) + 1,  2 * n1     , (2 * n1) + 1
								  };

			val = std::pow(x[j][i], penal);
			
			BOOST_MAT_INSERT(K, KE, &dof[0], 8, val);
		}
	}
	
    // Creation of Load
	F(1) = -1.0;
	
    // Generation of fixed and free degrees of freedom
    std::vector <unsigned int> fixeddof(nelemY + 1, 0);
	Generate_Numbers(fixeddof, 0, (nelemY + 1) * 2, 2);
	fixeddof.push_back(2 * (nelemX + 1) * (nelemY + 1) - 1);
	
    std::vector <unsigned int> alldof(2 * (nelemX + 1) * (nelemY + 1), 0);
	Generate_Numbers(alldof, 0, 2 * (nelemX + 1) * (nelemY + 1));
	
    std::vector <unsigned int> freedof;
	std::set_difference(alldof.begin(), alldof.end(), fixeddof.begin(), fixeddof.end(), std::inserter(freedof, freedof.begin()));
	
    // Creation of stiffness matrix for freedof
    mat A(freedof.size(), freedof.size());

	Vector b(freedof.size());
	Vector x1(freedof.size());

    // Extraction of stiffness matrix and load vector from global stiffness matrix and global load vector
    #pragma omp parallel for
	for (unsigned int i = 0; i < freedof.size(); i++){
		for (unsigned int j = 0; j < freedof.size(); j++)
			A(i, j) = K(freedof[i], freedof[j]);
		b(i) =  F(freedof[i]);
	}

    // Solving linear system of equation
	SOLVE_SYSTEM_EQUATIONS(x1, A, b, false, false);

    // assignment of solution to global domain
    #pragma omp parallel for
	for (unsigned int i = 0; i < freedof.size(); i++)
		U[freedof[i]] = x1(i);
	
    // Clear allocated memory
	x1.clear();
	A.clear();
	K.clear();
	F.clear();
}

