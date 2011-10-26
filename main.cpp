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

// Convolves a random matrix of |width| x |height|
// Prints out results (convolved matrix and min/max values).
// Times the computation.
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
    Matrix dx = testMatrix;
    dx.init();
    testMatrix.computeDx(dx, dxMin, dxMax);
    
    uchar dyMin;
    uchar dyMax;
    Matrix dy = testMatrix;
    dy.init();            
    testMatrix.computeDy(dy, dyMin, dyMax);
    
    end = clock();
    
    float timeDifference = ((float) (end - start)) / CLOCKS_PER_SEC;
    
    if (printMatrix) 
    {
        cout << testMatrix << endl;
        cout << dx << endl;
    }
    cout << "min: " << ((int) dxMin) << " max: " << 
        ((int)dxMax) << endl;
    
    if (printMatrix) 
    {
        cout << dy << endl;
        cout << "min: " << ((int) dyMin) << " max: " << 
            ((int)dyMax) << endl;
    }
    cout << "Ran in " << setprecision(4) << timeDifference << " seconds" << endl;
}

int main (int argc, const char * argv[]) {

    // just test
    if (argc == 1) 
    {
        basicTest();

        testRandom(12, 13);

        testRandom(1024, 2048, false);

    }
    else if(argc == 2)
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

