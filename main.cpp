//
//  main.cpp
//  Convolve

#include <iomanip>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"

using namespace Dog3d;
using namespace std;

// for threaded methods
Matrix g_matrix;
Matrix g_dx;
Matrix g_dy;
uchar g_dxMin;
uchar g_dxMax;
uchar g_dyMin;
uchar g_dyMax;

void testRandom(int width, int height, bool printMatrix=true);
void threadedTest(int width, int height, bool printMatrix=true);
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

    uchar dxMin;
    uchar dxMax;
    uchar dyMin;
    uchar dyMax;
    
    Matrix dx = testMatrix;
    dx.init();
    Matrix dy = testMatrix;
    dy.init();
    
    clock_t start;
    clock_t end;
    start = clock();

    testMatrix.computeDx(dx, dxMin, dxMax);         
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


// For the mult-thread test
void *computeDx(void *) 
{
    g_matrix.computeDx(g_dx, g_dxMin, g_dxMax);   
    return NULL;
}

void *computeDy(void *) 
{
    g_matrix.computeDy(g_dy, g_dyMin, g_dyMax);  
    return NULL; 
}

// Computes dX and dY of a random matrix of |width| x |height| 
// Prints out results (convolved matrices and min/max values).
// Times the computation and displays results.
void threadedTest(int width, int height, bool printMatrix) 
{
    g_matrix.init(width,height);    
    g_matrix.random();
    
    g_dx = g_matrix;
    g_dx.init();
    g_dy = g_matrix;
    g_dy.init();
    
    clock_t start;
    clock_t end;
    start = clock();

    int returnCode;
    pthread_t threads[2];
    
    returnCode = pthread_create(&threads[0], NULL, computeDx, NULL);
    computeDx(NULL);
    
    if (returnCode){
       printf("ERROR; return code from pthread_create() is %d\n", returnCode);
       exit(-1);
    }
    
    returnCode = pthread_create(&threads[1], NULL, computeDy, NULL);
    computeDy(NULL);
    if (returnCode){
       printf("ERROR; return code from pthread_create() is %d\n", returnCode);
       exit(-1);
    }
    
    end = clock();
    float timeDifference = ((float) (end - start)) / CLOCKS_PER_SEC;
    
    // Display results to cout
    if (printMatrix) 
    {
        cout << endl << "Random Matrix" << endl << endl;
        cout << g_matrix << endl;
        cout << "dX Matrix" << endl << endl;
        cout << g_dx << endl;
    }
    cout << "min: " << ((int) g_dxMin) << " max: " << 
        ((int)g_dxMax) << endl << endl;
    
    if (printMatrix) 
    {
        cout << "dY Matrix" << endl << endl; 
        cout << g_dy << endl;
        cout << "min: " << ((int) g_dyMin) << " max: " <<  ((int)g_dyMax) << endl << endl;
    }
    cout << "Convolution ran in " << setprecision(4) << timeDifference << " seconds" << endl;
    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_exit(NULL);
}

int main (int argc, const char * argv[]) {

    // just test
    if (argc == 1) 
    {
        cout << "Running basic test " << endl;
        basicTest();
        testRandom(12, 13);
        testRandom(1024, 2048, false);
    }
    else if(argc == 3)
    {
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);
            
        cout << "Running single-thread test " << endl;
        testRandom(width, height);
    }
    else if(argc == 4)
    {
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);
    
        cout << "Running multi-threaded test " << endl;
        threadedTest(width, height);
    }
    else 
    {
        cout << "Epic Fail" << endl;
    }

    return 0;
}

