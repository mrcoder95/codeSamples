/**
    Matrix Operations

    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "../main.h"

// Converting matrix (vector) to BOOST matrix
template <class MATRIX>
void BOOST_MAT_INSERT(MATRIX &A, std::vector <std::vector <double>> &mat, unsigned int *pos, unsigned int size, double val = 1.0) 
{
	for(unsigned int i = 0 ; i < size ; i++)
		for(unsigned int j = 0 ; j < size ; j++)
			A(pos[i], pos[j]) += val * mat[i][j];
}

// Generation of numbers
template <class Data_Type>
void Generate_Numbers (vector <Data_Type> &A, unsigned int start, unsigned int stop, unsigned int inc = 1)
{
	unsigned int j = 0;
	for (unsigned int i = start; i < stop; i += inc) 
		A[j++] = i;
}

// Vector (transpose), matrix and vector product
template <class Data_Type>
Data_Type VecT_Mat_Vec_Product (std::vector <std::vector <Data_Type>> &mat, Data_Type *A) 
{
	unsigned int SIZE = mat.size();
	Data_Type temp = 0.0;
	Data_Type ans = 0.0;

	for (unsigned int i = 0; i < SIZE; i++) {
		temp = 0.0;
		for (unsigned int j = 0; j < SIZE; j++)
			temp += A[j] * mat[i][j];
		ans += temp * A[i];
	}
	
	return ans;
}
