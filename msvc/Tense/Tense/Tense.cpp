// Tense.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<chrono>
#include"Matrix.hpp"

using namespace std;
using namespace Tense;


int main()
{
    Matrix A(5000, 5000, 3);

    
    double sample = 10;


    for (int j = 1; j <= 32; j++)
    {

        Tense::num_threads = j;
        double total = 0;
        for (int i = 0; i < sample; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            Matrix C = -A;
            auto end = chrono::high_resolution_clock::now();
            total += chrono::duration<double>(end - start).count();

        }
        cout << "Average time for "<<j<<" threads is " << (total / sample) << endl;
    }
}

