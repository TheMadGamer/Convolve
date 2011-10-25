//
//  Matrix.cpp
//  Convolve

#include <assert.h>
#include <iostream>

#include "Matrix.h"

using namespace Dog3d;
using namespace std;

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

void Matrix::identity() {
    // cannot set identity in non square matrix
    assert(m_width == m_height);
    
    zero();
    
    for( int i = 0; i < m_height; i++) {
        m_data[i * m_height + i] = 1;
    }
}


void Matrix::computeDx( Matrix &m ) const
{
    for(int i = 0; i < m_height; i++) 
    {
        const float *source_row = getRow(i);
        float *dest_row = m.getRow(i);
        
        float newValue = -*(source_row) + *(source_row+1);
        source_row++;
        *dest_row++ = newValue;
        for(int j = 1; j < m_width - 1; j++) 
        {
            newValue = -*(source_row-1) + *(source_row+1);
            source_row++;
           *dest_row++ = newValue;
        }
        
        newValue = -*(source_row-1) + *source_row;
        *dest_row = newValue;
    }
}

void Matrix::computeDy( Matrix &m ) const 
{

}

ostream &operator<<(ostream &stream, const Matrix &m) {
    for(int i = 0; i < m.height(); i++) {
        const float *row = m.getRow(i);
        for(int j = 0; j < m.width(); j++) {
            stream << *row++ << " ";
        }
        stream << std::endl;
    }
    return stream;
}
