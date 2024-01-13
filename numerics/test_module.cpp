#include <cmath>
#include <iomanip>
#include <iostream>

#include "band_diagonal_matrix.h"
#include "finite_difference.h"
#include "grid_generator.h"
#include "tridiagonal_matrix_solver.h"


int main() {

	const double x_min = -0.2;
	const double x_max = 0.2;
	const int order = 21;
	const double dx = (x_max - x_min) / (order - 1);

	std::vector<double> column_tmp(order, 0.0);

	TriDiagonal tri(order);
//	print_matrix(tri);

	PentaDiagonal penta(order);
//	print_matrix(penta);
	
	TriDiagonal d1dx1_ = d1dx1::c2(order, dx);
//	print_matrix(d1dx1_);

	d1dx1_.adjust_boundary(column_tmp);
	print_matrix(d1dx1_);

	std::vector<double> grid = grid_equidistant(x_min, x_max, order);
	std::cout << std::scientific << std::setprecision(5);

	std::vector<double> func;
	for (int i = 0; i != order; ++i)
		func.push_back(exp(2 * grid[i]));

	std::vector<double> deriv1 = d1dx1_.mat_vec_product(func);

	for (int i = 0; i != order; ++i) {

		std::cout 
			<< std::setw(3) << i 
			<< std::setw(14) << grid[i] 
			<< std::setw(14) << func[i]
			<< std::setw(14) << 2 * exp(2 * grid[i])
			<< std::setw(14) << deriv1[i]
			<< std::endl;

	}

	TriDiagonal d2dx2_ = d2dx2::c2(order, dx);
	print_matrix(d2dx2_);

	d2dx2_.adjust_boundary(column_tmp);
	print_matrix(d2dx2_);

	std::vector<double> deriv2 = d2dx2_.mat_vec_product(func);

	for (int i = 0; i != order; ++i) {

		std::cout
			<< std::setw(3) << i
			<< std::setw(14) << grid[i]
			<< std::setw(14) << func[i]
			<< std::setw(14) << 4 * exp(2 * grid[i])
			<< std::setw(14) << deriv2[i]
			<< std::endl;

	}

	std::vector<double> column(order, 1.0);

	tri_solver(d1dx1_, column);

	for (int i = 0; i != order; ++i) {

		std::cout
			<< std::setw(3) << i
			<< std::setw(14) << grid[i]
			<< std::setw(14) << column[i]
			<< std::endl;

	}


	return 0;
}