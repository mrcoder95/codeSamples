/*
          Copyright Gunter Winkler 2004 - 2007.
 					Distributed under the Boost Software License, Version 1.0.
    			(See accompanying file LICENSE_1_0.txt or copy at
          http://www.boost.org/LICENSE_1_0.txt)
 					authors: Gunter Winkler <guwi17 at gmx dot de>
          	Konstantin Kutzkow

				 This code is modified by
				 Mohamed Imran Peer Mohamed
				 Email: mrmdimran95@gmail.com
*/

#ifndef BOOST_GMRES_HPP
#define BOOST_GMRES_HPP

#include <iostream>
#include <iomanip>
#include <boost/timer.hpp>

#include "lin_op.hpp"
#include "orthogonal.hpp"
#include "precond.hpp"

typedef boost::numeric::ublas::compressed_matrix< double, boost::numeric::ublas::column_major > compressed_mat;
typedef boost::numeric::ublas::vector<double> Vector;
typedef boost::numeric::ublas::matrix< double, boost::numeric::ublas::column_major > mat;



template <class MATRIX>
void SOLVE_SYSTEM_EQUATIONS (	Vector &x,
								MATRIX &A,
								Vector &b,
								bool display_iteration = true,
								bool display_time = true)
{
	std::string endline = "===========================================================================================================\n";
	double tol = 1.0e-8; //the tolerance
	int N = b.size();
	unsigned int niter = 0;
	double actual_tol = 0.0;

	// set up linear operator T
	LinOp< MATRIX > T(A);

	// set up a simple preconditioner
	DiagonalPreconditioner< MATRIX > prec(A);



	boost::timer t_gmres;
	t_gmres.restart();

	// the test for the shortened version of the GMRes algorithm, the
	// search direction depends on the last 20 vectors of the
	// orthogonal basis

	x = b;

	// run GMRes and use \c mat_dense as type of temporary matrices
	niter = gmres_short< mat >(T, x, b, prec, 20, 3*N, tol);

	if (display_iteration || display_time)
		std::cout << endline;

	if (display_iteration)
		std::cout << "\tIteration 1 = " << niter << std::endl;

	{
		// compute residuum to check solution quality
		Vector resid( (T.image_size()) );
		T.residuum(x,b,resid);
		actual_tol = boost::numeric::ublas::norm_2(resid);
	}

	if (actual_tol > tol)
	{
		// the standard GMRes procedure with restarts after 20 steps, at most
		// 3 restarts are allowed
		x = b;

		niter = gmres_restarts< mat >(T, x, b, prec, 20, 3*N/20, tol);

		if (display_iteration)
			std::cout << "\tIteration 2 = " << niter << std::endl;

		{
			Vector resid( (T.image_size()) );
			T.residuum(x,b,resid);
			actual_tol = boost::numeric::ublas::norm_2(resid);
		}
	}

	if 	(actual_tol > tol)
	{
		// the test for the general GMRes algorithm, we allow no restarts
		// but up to N iterations which guarantees convergence
		x = b;
		niter = gmres_restarts< mat >(T, x, b, prec, N-1, 0, tol);

		if (display_iteration)
			std::cout << "\tIteration 3 = " << niter << std::endl;

		{
			Vector resid( (T.image_size()) );
			T.residuum(x,b,resid);
			actual_tol = boost::numeric::ublas::norm_2(resid);
		}
	}

	if (display_iteration)
		std::cout << "\tResidumm = " << actual_tol << std::endl;

	if (display_time)
		std::cout << "\tCPU time GMRES Solver = " << t_gmres.elapsed() << std::endl;

	if (display_iteration || display_time)
		std::cout << endline;

}

#endif	/* BOOST_GMRES_HPP */
