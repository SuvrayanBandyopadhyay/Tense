// Tense.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<chrono>
#include"Matrix.hpp"

using namespace std;
using namespace Tense;


int main()
{
    Matrix A(3, 2, {1,2,3,4,5,6});
    Matrix B(3, 2, {1,2,3,4,5,6});
    
    double sample = 10;


    for (int j = 1; j <= 16; j++)
    {

        Tense::num_threads = j;
        double total = 0;
        for (int i = 0; i < sample; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            Matrix C=A%B;
            auto end = chrono::high_resolution_clock::now();
            total += chrono::duration<double>(end - start).count();

        }
        cout << "Average time for "<<j<<" threads is " << (total / sample) << endl;
    }
    (A % B).display();
  
}

