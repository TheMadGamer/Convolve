//
//  main.cpp
//  Convolve


#include <iostream>

#include "Matrix.h"

using namespace Dog3d;
using namespace std;

int main (int argc, const char * argv[]) {

    // Create a small matrix.
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


    return 0;
}

