#include "matrix.h"
#include <stdexcept>

namespace MY_MATRIX {
	Matrix::Matrix() : rows(2), cols(2), data(rows * cols, 0.0) {};

	Matrix::~Matrix() = default;

	double& Matrix::operator()(size_t row, size_t col){
		if(col >= cols || row >= rows)
			throw std::out_of_range("index outside matrix.\n");
		return data[row * cols + col];
	}

	const double& Matrix::operator()(size_t row, size_t col) const {
		if(col >= cols || row >= rows)
			throw std::out_of_range("index outside matrix.\n");
		return data[row * cols + col];
	}

	// these two functions are practically useless because I've restricted
	// my implementation to 2x2 matrices only... but I'll keep them for 
	// aesthetic purposes.
	inline size_t Matrix::get_row_size() const {
		return rows;
	}

	inline size_t Matrix::get_col_size() const {
		return cols;
	}

	Matrix Matrix::operator+(const Matrix& otherMatrix){
		Matrix sum;
		for(int i = 0; i < data.size(); i++)
			sum.data[i] = this->data[i] + otherMatrix.data[i];
		return sum;
	}

	Matrix Matrix::operator*(double scalar){
		Matrix product;
		for(int i = 0; i < data.size(); i++)
			product.data[i] = this->data[i] * scalar;
		return product;
	}
}
