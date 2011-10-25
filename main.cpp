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
    
    Matrix dx = smallMatrix;
    Matrix dy = smallMatrix;
    
    smallMatrix.computeDx(dx);
    smallMatrix.computeDy(dy);
    
    

    return 0;
}

