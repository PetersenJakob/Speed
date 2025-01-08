#pragma once

#include <vector>


// Band-diagonal matrix stored in compact form.
template<typename Tnumber>
class BandDiagonalTemplate {

protected:

	// Matrix order: Number of elements along main diagonal.
	const std::size_t order_;
	// Lower bandwidth: Number of sub-diagonals.
	const std::size_t bandwidth_lower_;
	// Upper bandwidth: Number of super-diagonals.
	const std::size_t bandwidth_upper_;
	// Bandwidth: Maximum of bandwidth_lower_ and bandwidth_upper_.
	const std::size_t bandwidth_;
	// Number of diagonals.
	const std::size_t n_diagonals_;
	// Number of rows at lower boundary.
	const std::size_t n_boundary_rows_lower_;
	// Number of rows at upper boundary.
	const std::size_t n_boundary_rows_upper_;
	// Number of boundary rows.
	const std::size_t n_boundary_rows_;
	// Number of non-zero elements along each lower boundary row.
	const std::size_t n_boundary_elements_lower_;
	// Number of non-zero elements along each upper boundary row.
	const std::size_t n_boundary_elements_upper_;

public:

	// Band-diagonal matrix in compact form.
	// TODO: Store as row-major or column-major? See Scott Meyers youtube video.
	// TODO: Should this be private/protected?
	std::vector<std::vector<Tnumber>> matrix;
	// Lower boundary rows of band-diagonal matrix.
	std::vector<std::vector<Tnumber>> boundary_lower;
	// Upper boundary rows of band-diagonal matrix.
	std::vector<std::vector<Tnumber>> boundary_upper;

	// TODO: Default constructor removed since useless...

	BandDiagonalTemplate(
		const std::size_t _order,
		const std::size_t _bandwidth_lower,
		const std::size_t _bandwidth_upper,
		const std::size_t _n_boundary_rows_lower,
		const std::size_t _n_boundary_rows_upper,
		const std::size_t _n_boundary_elements_lower,
		const std::size_t _n_boundary_elements_upper);

	BandDiagonalTemplate(const BandDiagonalTemplate& mat);

	// TODO: Why is this inherited by derived classes?
	bool operator==(const BandDiagonalTemplate& m);

	int order() const {
		return order_;
	}

	int bandwidth_lower() const {
		return bandwidth_lower_;
	}

	int bandwidth_upper() const {
		return bandwidth_upper_;
	}

	int bandwidth() const {
		return bandwidth_;
	}

	int n_diagonals() const {
		return n_diagonals_;
	}

	int n_boundary_rows_lower() const {
		return n_boundary_rows_lower_;
	}

	int n_boundary_rows_upper() const {
		return n_boundary_rows_upper_;
	}

	int n_boundary_rows() const {
		return n_boundary_rows_;
	}

	int n_boundary_elements_lower() const {
		return n_boundary_elements_lower_;
	}

	int n_boundary_elements_upper() const {
		return n_boundary_elements_upper_;
	}

#if false
	// ...
	void gauss_elimination(
		const int boundary_row_idx,
		const int boundary_element_idx,
		const int matrix_row_idx,
		std::vector<double>& column);

	// ...
	void overwrite_bounary_row(const int boundary_row_idx);

	// ...
	virtual void adjust_boundary(std::vector<double>& column) {}
#endif
};


// Tri-diagonal matrix stored in compact form.
// TODO: Assumed, in other places, to have one boundary row!
// TODO: Remove _n_boundary_rows from parameter list!
template<typename Tnumber>
class TriDiagonalTemplate : public BandDiagonalTemplate<Tnumber> {

public:

	TriDiagonalTemplate(
		const std::size_t _order,
		const std::size_t _n_boundary_rows = 1,
		const std::size_t _n_boundary_elements = 3) :
		BandDiagonalTemplate<Tnumber>(_order, 1, 1, _n_boundary_rows, _n_boundary_elements) {}

	TriDiagonalTemplate(const TriDiagonalTemplate& mat) : 
		BandDiagonalTemplate<Tnumber>(mat) {};

	// TODO: Need to define ordinary assignment operator?

	TriDiagonalTemplate operator+(const TriDiagonalTemplate& rhs);

	TriDiagonalTemplate& operator+=(const TriDiagonalTemplate& rhs);

	TriDiagonalTemplate operator-(const TriDiagonalTemplate& rhs);

	TriDiagonalTemplate& operator-=(const TriDiagonalTemplate& rhs);

	TriDiagonalTemplate operator*(const Tnumber scalar);

	TriDiagonalTemplate& operator*=(const Tnumber scalar);

	// TODO: operator*(const TriDiagonalTemplate& rhs)?
	// TODO: operator*=(const TriDiagonalTemplate& rhs)?

#if false

	std::vector<double> operator*(const std::vector<double>& vector);

	TriDiagonal identity();

	TriDiagonal pre_vector(const std::vector<double>& vector);

	void adjust_boundary(std::vector<double>& column);
#endif
};


template<typename Tnumber>
TriDiagonalTemplate<Tnumber> operator*(
	const Tnumber scalar,
	TriDiagonalTemplate<Tnumber> rhs);


// Penta-diagonal matrix stored in compact form.
// TODO: Assumed, in other places, to have two boundary row!
// TODO: Remove _n_boundary_rows from parameter list!
template<typename Tnumber>
class PentaDiagonalTemplate : public BandDiagonalTemplate<Tnumber> {

public:

	PentaDiagonalTemplate(
		const int _order,
		const int _n_boundary_rows = 2,
		const int _n_boundary_elements = 3) :
		BandDiagonalTemplate<Tnumber>(_order, 2, 2, _n_boundary_rows, _n_boundary_elements) {}

	PentaDiagonalTemplate(const PentaDiagonalTemplate& mat) :
		BandDiagonalTemplate<Tnumber>(mat) {};

#if false
	PentaDiagonal operator*(const double scalar);

	std::vector<double> operator*(const std::vector<double>& vector);

	PentaDiagonal operator*=(const double scalar);

	PentaDiagonal operator+(const PentaDiagonal& rhs);

	PentaDiagonal operator+=(const PentaDiagonal& rhs);

	PentaDiagonal operator-(const PentaDiagonal& rhs);

	PentaDiagonal operator-=(const PentaDiagonal& rhs);

	PentaDiagonal identity();

	PentaDiagonal pre_vector(const std::vector<double>& vector);

	void adjust_boundary(std::vector<double>& column);
#endif
};


template<typename Tnumber, typename Tmatrix>
void scalar_add_matrixTemplate(
	const Tnumber scalar,
	Tmatrix& matrix);


template<typename Tnumber, typename Tmatrix>
void scalar_multiply_matrixTemplate(
	const Tnumber scalar,
	Tmatrix& matrix);


template<typename Tmatrix>
void matrix_add_matrixTemplate(
	const Tmatrix& matrix1,
	const Tmatrix& matrix2,
	Tmatrix& result);


// IMPLEMENT THIS!
template<typename Tnumber, typename Tmatrix>
void matrix_multiply_columnTemplate(
	const Tmatrix& matrix,
	const std::vector<Tnumber>& column,
	std::vector<Tnumber>& result);


// IMPLEMENT THIS!
template<typename Tnumber, typename Tmatrix>
void row_multiply_matrixTemplate(
	const std::vector<Tnumber>& vector,
	Tmatrix& matrix) {};


// ###############################################################################


// Band-diagonal matrix stored in compact form.
// Note: The lower and upper bandwidths are assumed to be identical.
class BandDiagonal {

protected:

	// Matrix order: Number of elements along main diagonal.
	int order_;
	// Bandwidth: Number of sub-diagonals or super-diagonals.
	int bandwidth_;
	// Number of diagonals.
	int n_diagonals_;
	// Number of boundary rows (at each boundary).
	int n_boundary_rows_;
	// Number of non-zero elements along each boundary row.
	int n_boundary_elements_;

public:

	// Band-diagonal matrix in compact form.
	std::vector<std::vector<double>> matrix;

	// Boundary rows of band-diagonal matrix.
	std::vector<std::vector<double>> boundary_rows;

	std::vector<std::vector<double>> boundary_rows_tmp;

	BandDiagonal();

	BandDiagonal(
		const int _order,
		const int _bandwidth,
		const int _n_boundary_rows,
		const int _n_boundary_elements);

	BandDiagonal(const BandDiagonal& mat);

	// Why is this inherited by derived classes?
	bool operator==(const BandDiagonal& m);

	int order() const {
		return order_;
	}

	int bandwidth() const {
		return bandwidth_;
	}

	int n_diagonals() const {
		return n_diagonals_;
	}

	int n_boundary_rows() const {
		return n_boundary_rows_;
	}

	int n_boundary_elements() const {
		return n_boundary_elements_;
	}

	// ...
	void gauss_elimination(
		const int boundary_row_idx,
		const int boundary_element_idx,
		const int matrix_row_idx,
		std::vector<double>& column);

	// ...
	void overwrite_bounary_row(const int boundary_row_idx);

	// ...
	virtual void adjust_boundary(std::vector<double>& column) {}

};


// Tri-diagonal matrix stored in compact form.
// TODO: Assumed, in other places, to have one boundary row!
// Remove _n_boundary_rows from parameter list!
class TriDiagonal : public BandDiagonal {

public:

	TriDiagonal() {}

	TriDiagonal(
		const int _order,
		const int _n_boundary_rows = 1,
		const int _n_boundary_elements = 3) : 
		BandDiagonal(_order, 1, _n_boundary_rows, _n_boundary_elements) {}

	TriDiagonal operator*(const double scalar);

	std::vector<double> operator*(const std::vector<double>& vector);

	TriDiagonal operator*=(const double scalar);

	TriDiagonal operator+(const TriDiagonal& rhs);

	TriDiagonal operator+=(const TriDiagonal& rhs);

	TriDiagonal operator-(const TriDiagonal& rhs);

	TriDiagonal operator-=(const TriDiagonal& rhs);

	TriDiagonal identity();

	TriDiagonal pre_vector(const std::vector<double>& vector);

	void adjust_boundary(std::vector<double>& column);

};


// Penta-diagonal matrix stored in compact form.
// TODO: Assumed, in other places, to have two boundary row!
// Remove _n_boundary_rows from parameter list!
class PentaDiagonal : public BandDiagonal {

public:

	PentaDiagonal() {}

	PentaDiagonal(
		const int _order,
		const int _n_boundary_rows = 2,
		const int _n_boundary_elements = 3) : 
		BandDiagonal(_order, 2, _n_boundary_rows, _n_boundary_elements) {}

	PentaDiagonal operator*(const double scalar);

	std::vector<double> operator*(const std::vector<double>& vector);

	PentaDiagonal operator*=(const double scalar);

	PentaDiagonal operator+(const PentaDiagonal& rhs);

	PentaDiagonal operator+=(const PentaDiagonal& rhs);

	PentaDiagonal operator-(const PentaDiagonal& rhs);

	PentaDiagonal operator-=(const PentaDiagonal& rhs);

	PentaDiagonal identity();

	PentaDiagonal pre_vector(const std::vector<double>& vector);

	void adjust_boundary(std::vector<double>& column);

};


TriDiagonal operator*(
	const double scalar, 
	TriDiagonal rhs);


PentaDiagonal operator*(
	const double scalar, 
	PentaDiagonal rhs);


template<class T>
void scalar_multiply_matrix(
	const double scalar, 
	T& matrix);


template<class T>
void matrix_multiply_vector(
	const T& matrix, 
	const std::vector<double>& vector, 
	std::vector<double>& result);


template<class T>
void matrix_add_matrix(
	const T& matrix1, 
	const T& matrix2, 
	T& result);


void print_matrix(BandDiagonal matrix);


template<class T>
void row_multiply_matrix(
	T& matrix,
	const std::vector<double>& vector);
