//
//  main.cpp
//  Convolve


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

using namespace Dog3d;
using namespace std;

void testRandom(int width, int height);
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
        
    smallMatrix.computeDx(dx);
    smallMatrix.computeDy(dy);
    
    std::cout << dx << endl;
    std::cout << dy << endl;
    
    // Test a grey band
    smallMatrix.greyStreak();
    
    std::cout << smallMatrix << endl;
    
    smallMatrix.computeDx(dx);
    smallMatrix.computeDy(dy);
    
    std::cout << dx << endl;
    std::cout << dy << endl;
}

void testRandom(int width, int height) 
{
    
    Matrix testMatrix;
    testMatrix.init(width,height);
    
    testMatrix.random();
    
    Matrix dx = testMatrix;
    dx.init();
    testMatrix.computeDx(dx);
        
    Matrix dy = testMatrix;
    dy.init();            
    testMatrix.computeDy(dy);
    
    cout << testMatrix << endl;
    cout << dx << endl;
    cout << dy << endl;

}

int main (int argc, const char * argv[]) {

    // just test
    if (argc == 1) 
    {
        basicTest();

        testRandom(12, 13);

    } 
    else if(argc == 2)
    {
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);
    
        Matrix testMatrix;
        testMatrix.init(width,height);
        
        testMatrix.random();
        
        Matrix dx = testMatrix;
        dx.init();
        testMatrix.computeDx(dx);
            
        Matrix dy = testMatrix;
        dy.init();            
        testMatrix.computeDy(dy);
        
    }
    else 
    {
        cout << "Epic fail" << endl;
    }

    return 0;
}

