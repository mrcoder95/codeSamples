/**
	File to include all the required header files

	Created by:	Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#ifndef MAIN_H_
#define MAIN_H_

// Basic Libraries
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>

#ifndef mini
#define mini(a,b)		(((a) < (b)) ? (a) : (b))
#endif

#ifndef maxi
#define maxi(a,b)		(((a) > (b)) ? (a) : (b))
#endif

// BOOST Library Header Files
#include <boost/timer.hpp>
#include "solver/lin_op.hpp"
#include "solver/orthogonal.hpp"
#include "solver/precond.hpp"

// Required Files specific to the program
#include "solver/boost_gmres.hpp"
#include "src_line/line_topology.h"
#include "src_line/mat_operations.cpp"
#include "src_line/FEA.cpp"
#include "src_line/Build_Stiffness_Matrix.cpp"
#include "src_line/Mesh_Filter.cpp"
#include "src_line/Opt_Crt_Update.cpp"

#endif 	/*	MAIN_H_	*/
