//
//  Matrix.h
//  Convolve


#ifndef Convolve_Matrix_h
#define Convolve_Matrix_h

#include <assert.h>

typedef unsigned char uchar;

namespace Dog3d 
{
    // Dense matrix for computing finite difference derivatives
    class Matrix 
    {

    public:
        Matrix() : m_data(NULL),
              m_height(0),
              m_width(0) {}

        Matrix(Matrix &m) : m_data(NULL)
        {
            m_width = m.m_width;
            m_height = m.m_height;
        }

        virtual ~Matrix();    

        void init() 
        {
            m_data = new uchar[m_width * m_height];
            assert(m_data);
        }

        void init(int width, int height);

            
        inline void zero() { memset(m_data, 0, m_width*m_height*sizeof(uchar));}
  
        // simple test routines
        void identity();
        void greyStreak();

        // random data
        void random();
        
        // Computes finite difference derivatives (ie convolves in x,y directions with [-1 0 1])
        void computeDx( Matrix &m, uchar &dxMin, uchar &dxMax ) const;
        void computeDy( Matrix &m, uchar &dyMin, uchar &dyMax ) const;

        // inline row accessors
        inline const uchar *getRow(int i) const 
        {
            return m_data + (i * m_width);
        }

        inline uchar *getRow(int i) 
        {
            return m_data + (i * m_width);
        }

        inline int width() const { return m_width; }
        inline int height() const { return m_height; }
  
      private:
        uchar *m_data;
        int m_width;
        int m_height;
    };
}

// output a matrix in square form to a stream
std::ostream &operator<<(std::ostream &stream, const Dog3d::Matrix &m);

#endif
