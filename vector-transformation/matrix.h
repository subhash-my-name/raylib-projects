#pragma once
#include <stdexcept>
#include <vector>


// wasted too much to realize the namespace problem.
// raylib has its own Struct named 'Matrix'
namespace MY_MATRIX { 
	class Matrix{
		size_t rows;
		size_t cols;
		// I searched online a little bit and found that we can 
		// store matrix values in a 1D vector using 
		// some basic arithmetic manipulation.
		std::vector<double> data; 

	public:
		Matrix();
		~Matrix();

		// for convenience purposes, i thought it would 
		// be better if I
		// overload the '()' to read/write indices of a matrix instance/reference
	
		double& operator()(size_t, size_t);
		const double& operator()(size_t, size_t) const;

		Matrix operator+(const Matrix&);
		Matrix operator*(double);
		
		inline size_t get_row_size() const;
		inline size_t get_col_size() const;
	};
}
