//
//  main.cpp
//  Convolve

#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"

using namespace Dog3d;
using namespace std;

void testRandom(int width, int height, bool printMatrix=true);
void basicTest();

// Tests two small matrices
void basicTest() {
    // Create a small matrix
    // Test identity
    Matrix smallMatrix;
    smallMatrix.init(10,10);
    smallMatrix.identity();
    
    std::cout << smallMatrix << endl;
    
    Matrix dx = smallMatrix;
    dx.init();
    Matrix dy = smallMatrix;
    dy.init();
    
    uchar dxMin;
    uchar dxMax;
    uchar dyMin;
    uchar dyMax;
    
    smallMatrix.computeDx(dx, dxMin, dxMax);
    smallMatrix.computeDy(dy, dyMin, dyMax);
    std::cout << dx << endl;
    std::cout << dy << endl;
    
    // Test a grey band
    smallMatrix.greyStreak();
    std::cout << smallMatrix << endl;
    
    smallMatrix.computeDx(dx, dxMin, dxMax);
    smallMatrix.computeDy(dy, dyMin, dyMax);
    std::cout << dx << endl;
    std::cout << dy << endl;
}

// Computes dX and dY of a random matrix of |width| x |height| 
// Prints out results (convolved matrices and min/max values).
// Times the computation and displays results.
void testRandom(int width, int height, bool printMatrix) 
{
    Matrix testMatrix;
    testMatrix.init(width,height);
    
    testMatrix.random();
    
    clock_t start;
    clock_t end;
    start = clock();
    
    uchar dxMin;
    uchar dxMax;
    uchar dyMin;
    uchar dyMax;
    
    Matrix dx = testMatrix;
    dx.init();
    testMatrix.computeDx(dx, dxMin, dxMax);
    
    Matrix dy = testMatrix;
    dy.init();            
    testMatrix.computeDy(dy, dyMin, dyMax);
    
    end = clock();
    float timeDifference = ((float) (end - start)) / CLOCKS_PER_SEC;
    
    // Display results to cout
    if (printMatrix) 
    {
        cout << endl << "Random Matrix" << endl << endl;
        cout << testMatrix << endl;
        cout << "dX Matrix" << endl << endl;
        cout << dx << endl;
    }
    cout << "min: " << ((int) dxMin) << " max: " << 
        ((int)dxMax) << endl << endl;
    
    if (printMatrix) 
    {
        cout << "dY Matrix" << endl << endl; 
        cout << dy << endl;
        cout << "min: " << ((int) dyMin) << " max: " <<  ((int)dyMax) << endl << endl;
    }
    cout << "Convolution ran in " << setprecision(4) << timeDifference << " seconds" << endl;
}

int main (int argc, const char * argv[]) {

    // just test
    if (argc == 1) 
    {
        basicTest();
        testRandom(12, 13);
        testRandom(1024, 2048, false);
    }
    else if(argc == 3)
    {
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);
    
        testRandom(width, height);
    }
    else 
    {
        cout << "Epic fail" << endl;
    }

    return 0;
}

