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
    
    m_data = new uchar[width * height];
    assert(m_data);
}

void Matrix::identity() {
    // cannot set identity in non square matrix
    assert(m_width == m_height);
    
    zero();
    
    for( int i = 0; i < m_height; i++) 
    {
        m_data[i * m_height + i] = 1;
    }
}

void Matrix::greyStreak() 
{
    // cannot set identity in non square matrix
    assert(m_width == m_height);
    
    zero();
    
    for( int i = 0; i < m_height; i++) 
    {
        m_data[i * m_height + i] = 100;
    }
}

void Matrix::random() 
{     
    uchar *data = m_data;
    uchar *end = data + m_height * m_width;
    
    while(data != end)
    {
        *data++ = rand();
    }
}

// prevent over/underflow
static inline uchar clampDifference(unsigned int lower, unsigned int upper)
{
    int newValue = upper - lower;

    if (newValue < 0) 
    {
        return 0;
    }
    else 
    {
        return newValue;
    }
}

void Matrix::computeDx( Matrix &m, uchar &dxMin, uchar &dxMax ) const
{
    dxMin = 255;
    dxMax = 0;

    for(int i = 0; i < m_height; i++) 
    {
        const uchar *source_row = getRow(i);
        uchar *dest_row = m.getRow(i);
        
        // first column
        {
            uchar value = clampDifference(*(source_row), *(source_row+1));
            if (value > dxMax) 
            {
                dxMax = value;
            }
            if (value < dxMin) 
            {
                dxMin = value;
            }
            *dest_row++ = value;
            source_row++;
        }
        
        // everything in between
        for(int j = 1; j < m_width - 1; j++) 
        {
            uchar value = clampDifference(*(source_row-1), *(source_row+1));
            if (value > dxMax) 
            {
                dxMax = value;
            }
            if (value < dxMin) 
            {
                dxMin = value;
            }
            *dest_row++ = value;
            source_row++;
        }
        
        // last column
        {
            uchar value = clampDifference(*(source_row-1), *source_row);
            if (value > dxMax) 
            {
                dxMax = value;
            }
            if (value < dxMin) 
            {
                dxMin = value;
            }
            
            *dest_row++ = value;
        }
    }
}

void Matrix::computeDy( Matrix &m, uchar &dyMin, uchar &dyMax  ) const 
{
    dyMin = 255;
    dyMax = 0;
    {
        const uchar *source_row_lower = getRow(0);
        const uchar *source_row_upper = getRow(1);
        uchar *dest_row = m.getRow(0);
        for(int j = 0; j < m_width; j++) 
        {
            uchar value = clampDifference(*(source_row_lower++), *(source_row_upper++));
            if (dyMin > value)
            {
                dyMin = value;
            }
            if (dyMax < value)
            {
                dyMax = value;
            }
            *dest_row++ = value;
        }
    }
    
    for(int i = 1; i < m_height-1; i++) 
    {
        const uchar *source_row_lower = getRow(i-1);
        const uchar *source_row_upper = getRow(i+1);
        
        uchar *dest_row = m.getRow(i);
        for(int j = 0; j < m_width; j++) 
        {
            uchar value = clampDifference(*(source_row_lower++), *(source_row_upper++));
            
            if (dyMin > value)
            {
                dyMin = value;
            }
            if (dyMax < value)
            {
                dyMax = value;
            }
            
            *dest_row++ = value;
        }
    }
    
    {
        const uchar *source_row_lower = getRow(m.height()-2);
        const uchar *source_row_upper = getRow(m.height()-1);
        uchar *dest_row = m.getRow(m.height()-1);
        for(int j = 0; j < m_width; j++) 
        {
            uchar value = clampDifference(*(source_row_lower++), *(source_row_upper++));
            
            if (dyMin > value)
            {
                dyMin = value;
            }
            if (dyMax < value)
            {
                dyMax = value;
            }
            
            *dest_row++ = value;
        }
    }
}

ostream &operator<<(ostream &stream, const Matrix &m) {
    for(int i = 0; i < m.height(); i++) 
    {
        const uchar *row = m.getRow(i);
        for(int j = 0; j < m.width(); j++)
        {
            stream << ((int) *row++) << " ";
        }
        stream << std::endl;
    }
    return stream;
}
