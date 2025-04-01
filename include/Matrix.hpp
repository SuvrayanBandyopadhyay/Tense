#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<initializer_list>
#include<algorithm>

namespace Tense 
{
	//Number of threads
	extern float num_threads;

	class Matrix 
	{

	private:
		//Private variables
		std::vector<float>_data;
		size_t _rows;
		size_t _columns;
	public:



		//Constructors
		Matrix(size_t rows,size_t columns, std::initializer_list<float> data);
		Matrix(size_t rows, size_t columns, std::vector<float> data);
		Matrix(size_t rows, size_t columns, float val=0);
		//Matrix attributes
		size_t rows();
		size_t columns();
		//display
		void display();

		std::vector<float>raw_data();
		//Set and at functions

		

		void set(size_t r, size_t c,float val);
		float at(size_t r, size_t c);

		//Flattened counterparts
		inline void flat_set(size_t index, float val);
		inline float flat_at(size_t index);

		//Unary operators
		Matrix operator -();
		
		//Binary operators
		Matrix operator +(Matrix b);
		void operator +=(Matrix b);
		Matrix operator -(Matrix b);
		void operator -=(Matrix b);

		//Matrix Multiplication
		Matrix operator *(Matrix b);
		void operator *=(Matrix b);
		
		//Hadamard product
		Matrix operator %(Matrix b);
		void operator%=(Matrix b);

		//Transpose
		Matrix transpose(Matrix b);
	};
}