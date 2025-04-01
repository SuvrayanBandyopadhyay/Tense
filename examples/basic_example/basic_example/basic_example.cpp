// basic_example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Tense.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<chrono>
#include<Matrix.hpp>

using namespace std;
using namespace Tense;


int main()
{
    Matrix A(500,400,1.25);
    Matrix B(400,300,2.31);

    double sample = 10;


    for (int j = 1; j <= 16; j++)
    {

        Tense::num_threads = j;
        double total = 0;
        for (int i = 0; i < sample; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            Matrix C = A * B;
            auto end = chrono::high_resolution_clock::now();
            total += chrono::duration<double>(end - start).count();

        }
        cout << "Average time for " << j << " threads is " << (total / sample) << endl;
    }
    return 0;

}

