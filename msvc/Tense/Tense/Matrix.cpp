#include"Matrix.hpp"
using namespace std;
using namespace Tense;

//Number of threads
float Tense::num_threads = 4;

//Constructors
Matrix::Matrix(size_t rows, size_t columns, vector<float>data) 
{
	_rows = rows;
	_columns = columns;
	_data = data;
}

Matrix::Matrix(size_t rows, size_t columns, initializer_list<float>data)
{
	_rows = rows;
	_columns = columns;
	_data = data;
}

Matrix::Matrix(size_t rows, size_t columns, float data)
{
	_rows = rows;
	_columns = columns;
	_data = vector<float>(rows * columns, data);
}
//Attributes
size_t Matrix::rows()
{
	return _rows;
}
size_t Matrix::columns() 
{
	return _columns;
}
vector<float>Matrix::raw_data() 
{
	return _data;
}
//Set and at functions
void Matrix::set(size_t r, size_t c, float val) 
{
	_data[r * _rows + c] = val;
}

float Matrix::at(size_t r, size_t c) 
{
	return _data[r * _rows + c];
}

//Flattened
void Matrix::flat_set(size_t index,float val)
{
	_data[index] = val;
}


float Matrix::flat_at(size_t index)
{
	return _data[index];
}

//Unary operator
void negate_section(size_t start,size_t end,Matrix &a,Matrix &c) 
{

	for (size_t i = start; i < end; i++) 
	{
		c.flat_set(i, -a.flat_at(i));
	}
}

Matrix Matrix::operator-() 
{
	Matrix c(_rows, _columns);
	

	size_t len = _rows * _columns /Tense::num_threads;


	//The threads
	vector<thread>threads;

	size_t end = _rows * _columns;
	for (size_t i = 0; i < end; i += len) 
	{
		//Parallelize using threading
		size_t t = min(i + len, end);

	
		threads.emplace_back(negate_section, i, t, std::ref(*this), std::ref(c));
	}

	for (auto& thread : threads) 
	{
		thread.join();
	}
	return c;
}

