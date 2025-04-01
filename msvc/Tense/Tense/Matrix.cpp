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
//Display function
void Matrix::display() 
{
	cout << "["<<endl;
	for (size_t i = 0; i < _rows; i++) 
	{
		cout << "[";
		for (size_t j = 0; j < _columns; j++) 
		{
			cout << at(i,j)<<" ";
		}
		cout <<"]"<< endl;
	}
	cout << "]";
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
	_data[r * _columns + c] = val;
}

float Matrix::at(size_t r, size_t c) 
{
	return _data[r * _columns + c];
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
	

	size_t len = (_rows * _columns /Tense::num_threads)+1;


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

//Binary operators
//Addition
void add_section(size_t start, size_t end, Matrix& a,Matrix& b, Matrix& c)
{

	for (size_t i = start; i < end; i++)
	{
		c.flat_set(i, a.flat_at(i)+b.flat_at(i));
	}
}

Matrix Matrix::operator+(Matrix b)
{
	Matrix c(_rows, _columns);


	size_t len = (_rows * _columns / Tense::num_threads)+1;


	//The threads
	vector<thread>threads;

	size_t end = _rows * _columns;
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);


		threads.emplace_back(add_section, i, t, std::ref(*this),std::ref(b), std::ref(c));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
	return c;
}

void Matrix::operator+=(Matrix b) 
{
	Matrix c(_rows, _columns);


	size_t len = (_rows * _columns / Tense::num_threads)+1;


	//The threads
	vector<thread>threads;

	size_t end = _rows * _columns;
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);


		threads.emplace_back(add_section, i, t, std::ref(*this), std::ref(b), std::ref(*this));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}

//Addition
void sub_section(size_t start, size_t end, Matrix& a, Matrix& b, Matrix& c)
{

	for (size_t i = start; i < end; i++)
	{
		c.flat_set(i, a.flat_at(i) - b.flat_at(i));
	}
}

Matrix Matrix::operator-(Matrix b)
{
	Matrix c(_rows, _columns);


	size_t len = (_rows * _columns / Tense::num_threads)+1;


	//The threads
	vector<thread>threads;

	size_t end = _rows * _columns;
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);


		threads.emplace_back(sub_section, i, t, std::ref(*this), std::ref(b), std::ref(c));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
	return c;
}

void Matrix::operator-=(Matrix b)
{
	Matrix c(_rows, _columns);


	size_t len = (_rows * _columns / Tense::num_threads)+1;


	//The threads
	vector<thread>threads;

	size_t end = _rows * _columns;
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);


		threads.emplace_back(sub_section, i, t, std::ref(*this), std::ref(b), std::ref(*this));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}

//Multiplication
void mult_section(size_t start, size_t end, Matrix& a, Matrix& b, Matrix& c) 
{
	for (size_t q = start; q < end; q++)
	{
		//Find values
		size_t row = q / c.columns();
		size_t column = q % c.columns();

		float val = 0;
		for (size_t k = 0; k < a.columns(); k++) 
		{
			val += a.at(row, k) * b.at(k, column);
		}
	
		c.flat_set(q, val);
	}

}

Matrix Matrix::operator*(Matrix b)
{
	Matrix c(_rows, b.columns());


	size_t len = (_rows * _columns / Tense::num_threads)+1;


	//The threads
	vector<thread>threads;

	size_t end = c.rows() * c.columns();
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);

	
		threads.emplace_back(mult_section, i, t, std::ref(*this), std::ref(b), std::ref(c));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
	return c;
}

void Matrix::operator*=(Matrix b)
{
	Matrix c(_rows, b.columns());


	size_t len = (_rows * _columns / Tense::num_threads)+1;


	//The threads
	vector<thread>threads;

	size_t end = c.rows() * c.columns();
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);


		threads.emplace_back(mult_section, i, t, std::ref(*this), std::ref(b), std::ref(*this));
		;
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}

//Hadamard Product
void hadamard_section(size_t start, size_t end, Matrix& a, Matrix& b, Matrix& c)
{

	for (size_t i = start; i < end; i++)
	{
		c.flat_set(i, a.flat_at(i) * b.flat_at(i));
	}
}

Matrix Matrix::operator%(Matrix b)
{
	Matrix c(_rows, _columns);


	size_t len = (_rows * _columns / Tense::num_threads) + 1;


	//The threads
	vector<thread>threads;

	size_t end = _rows * _columns;
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);


		threads.emplace_back(hadamard_section, i, t, std::ref(*this), std::ref(b), std::ref(c));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
	return c;
}

void Matrix::operator%=(Matrix b)
{
	Matrix c(_rows, _columns);


	size_t len = (_rows * _columns / Tense::num_threads) + 1;


	//The threads
	vector<thread>threads;

	size_t end = _rows * _columns;
	for (size_t i = 0; i < end; i += len)
	{
		//Parallelize using threading
		size_t t = min(i + len, end);


		threads.emplace_back(hadamard_section, i, t, std::ref(*this), std::ref(b), std::ref(*this));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}

