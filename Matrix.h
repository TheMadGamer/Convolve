//
//  Matrix.h
//  Convolve


#ifndef Convolve_Matrix_h
#define Convolve_Matrix_h

namespace Dog3d {

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
      void init(int width, int height);
      
      void computeDx( Matrix &m ) const;
      void computeDy( Matrix &m ) const;
       
      inline const float *getRow(int i) const {
          return m_data + (i * m_width);
      }
      
    private:
      float *m_data;
      int m_width;
      int m_height;
  };

}

#endif
