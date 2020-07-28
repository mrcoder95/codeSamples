/**
	Building Stiffness Matrix
	
    Original Code was developed by Ole Sigmund in MATLAB.
    Source: https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

    The MATLAB code is converted to C++ code.
	Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "../main.h"

void LineToplogy::Build_Stiffness_Matrix ()
{
	double nu = 0.3;
	
	double factor = E / (1. - std::pow(nu, 2));
	
	double k[8] = { factor * (( 1. / 2.) - (nu /  6.)), factor * (( 1. / 8.) + ( nu / 8.)), factor * ((-1. / 4.) + (-nu / 12.)), factor * ((-1. / 8.) + ( 3. * nu / 8.)),
					factor * ((-1. / 4.) + (nu / 12.)), factor * ((-1. / 8.) + (-nu / 8.)), factor * (             ( nu /  6.)), factor * (( 1. / 8.) + (-3. * nu / 8.)) 
				  };
	
	KE.resize(8);
	
	KE[0].insert (KE[0].begin(), { k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7] });
	KE[1].insert (KE[1].begin(), { k[1], k[0], k[7], k[6], k[5], k[4], k[3], k[2] });
	KE[2].insert (KE[2].begin(), { k[2], k[7], k[0], k[5], k[6], k[3], k[4], k[1] });
	KE[3].insert (KE[3].begin(), { k[3], k[6], k[5], k[0], k[7], k[2], k[1], k[4] });
	KE[4].insert (KE[4].begin(), { k[4], k[5], k[6], k[7], k[0], k[1], k[2], k[3] });
	KE[5].insert (KE[5].begin(), { k[5], k[4], k[3], k[2], k[1], k[0], k[7], k[6] });
	KE[6].insert (KE[6].begin(), { k[6], k[3], k[4], k[1], k[2], k[7], k[0], k[5] });
	KE[7].insert (KE[7].begin(), { k[7], k[2], k[1], k[4], k[3], k[6], k[5], k[0] });
}
