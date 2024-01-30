#include <iostream>
#include <vector>

#include "band_diagonal_matrix.h"
#include "tridiagonal_matrix_solver.h"

void tri_solver(TriDiagonal& matrix, std::vector<double>& column) {

#if false
	print_matrix(matrix);
	std::cout << "Column vector before: " << std::endl;
	for (int i = 0; i != column.size(); ++i) {
		std::cout << column[i] << std::endl;
	}
	std::cout << std::endl;
#endif

//	matrix.adjust_boundary
	matrix.adjust_boundary(column);

#if false
	print_matrix(matrix);
	std::cout << "Column vector after: " << std::endl;
	for (int i = 0; i != column.size(); ++i) {
		std::cout << column[i] << std::endl;
	}
	std::cout << std::endl;
#endif

	tridiagonal_matrix_solver(
		matrix.matrix[0],
		matrix.matrix[1],
		matrix.matrix[2],
		column);

}


void tridiagonal_matrix_solver(
	std::vector<double>& sub,
	std::vector<double>& main,
	std::vector<double>& super,
	std::vector<double>& column) {

	// Number of elements along main diagonal.
	const int n_elements = main.size();

	// Store modified elements of super-diagonal.
	std::vector<double> super_tmp(n_elements, 0.0);

	// Temporary index.
	int idx_tmp = 0;

	// *****************************************************************
	// Forward sweep. Remove sub-diagonal elements by Gauss elimination.
	// *****************************************************************

	// Denominator for normalization of 1st element of main diagonal.
	double denominator = main[0];

	// 1st element of super-diagonal after normalization.
	super_tmp[0] = super[0] / denominator;

	// 1st element of column matrix after normalization.
	column[0] /= denominator;

	for (int i = 1; i != n_elements; ++i) {

		idx_tmp = i - 1;

		// Denominator for normalization of (i + 1)'th element of main diagonal.
		denominator = main[i] - sub[i] * super_tmp[idx_tmp];

		// (i + 1)'th element of super-diagonal after Gauss elimination.
		super_tmp[i] = super[i] / denominator;

		// (i + 1)'th element of column matrix after Gauss elimination.
		column[i] = (column[i] - sub[i] * column[idx_tmp]) / denominator;

	}

	// ***********************************************************************
	// Back substitution. Remove super-diagonal elements by Gauss elimination.
	// ***********************************************************************

	for (int i = n_elements - 2; i != -1; --i) {

		idx_tmp = i + 1;

		// (i + 1)'th element of column matrix after Gauss elimination.
		column[i] -= super_tmp[i] * column[idx_tmp];

	}

}
