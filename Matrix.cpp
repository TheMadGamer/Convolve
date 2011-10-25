//
//  Matrix.cpp
//  Convolve

#include <assert.h>
#include <iostream>

#include "Matrix.h"

using namespace Dog3d;

Matrix::~Matrix() 
{
    if (m_data) 
    {
        delete [] m_data;
        m_data = NULL;
        m_width = 0;
        m_height = 0;
    }
}

void Matrix::init(int width, int height) 
{
    m_width = width;
    m_height = height;
    
    m_data = new float[width * height];
    assert(m_data);
}

void Matrix::computeDx( Matrix &m ) const {

}

void Matrix::computeDy( Matrix &m ) const {

}
