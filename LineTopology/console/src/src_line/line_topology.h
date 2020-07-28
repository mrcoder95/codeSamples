/**
    Line Topology Class Declaration

    Original Code was developed by Ole Sigmund in MATLAB.
    Source: https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

    The MATLAB code is converted to C++ code.
    Created by: Mohamed Imran Peer Mohamed
		Email: mrmdimran95@gmail.com
*/

#ifndef LINE_TOPOLOGY_CLASS_H_
#define LINE_TOPOLOGY_CLASS_H_


#include "../main.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// Boost Library
typedef boost::numeric::ublas::compressed_matrix< double, boost::numeric::ublas::column_major > compressed_mat;
typedef boost::numeric::ublas::vector<double> Vector;
typedef boost::numeric::ublas::matrix< double, boost::numeric::ublas::column_major > mat;

class LineToplogy {
	public:
		unsigned int nelemX;								// Number of Elements in X
		unsigned int nelemY;								// Number of Elements in Y
		double volfrac;											// Volume Fraction
		double penal;												// Penalization Power
		double rmin;												// Filter Size
		double E;											// Material Young's Modulus

		std::vector <double> U;
		vector <vector <double>> KE;
		vector <vector <double>> DC;
		vector <vector <double>> DCN;

		LineToplogy (	unsigned int x, unsigned int y,
						double vol,     double penal_val,
						double rmin_val, double E1)
		{
			nelemX = x;
			nelemY = y;
			volfrac = vol;
			penal = penal_val;
			rmin = rmin_val;
			E = E1;

			Build_Stiffness_Matrix();
			DC.resize(nelemY, vector <double>(nelemX, 0.0));
		}

		void FEA(vector <vector <double>> &x);

		void Build_Stiffness_Matrix();

		void Mesh_Filter(vector <vector <double>> &x);

		void Opt_Crt_Update(vector <vector <double>> &x);

		~LineToplogy()
		{
			U.clear();
			KE.clear();
			DC.clear();
			DCN.clear();
		}

};

#endif	/*	LINE_TOPOLOGY_CLASS_H_	*/
