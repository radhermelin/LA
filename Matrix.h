#ifndef MATRIX_H
#define MATRIX_H

template <class T>
class Matrix
{
    public:
        // Constructor methods
        Matrix();
        Matrix(const int rows, const int columns);
        Matrix(const int rows, const int columns, const T *inputData);
        Matrix(const Matrix<T> &inputMatrix);

        // Class destructor
        ~Matrix();

        // Configuration
        bool resize(const int rows, const int columns);

        // Getters and Setters
        T getEntry(const int row, const int column) const;
        bool setEntry(const int row, const int column, const T value);
        int getRows() const;
        int getColumns() const;

        // Overload equals operator
        bool operator ==(const Matrix<T> &input);

        // Overload +, - and * operators
        template <class U> friend Matrix<U> operator +(const Matrix<U> &left, const Matrix<U> &right);
        template <class U> friend Matrix<U> operator +(const U &left, const Matrix<U> &right);
        template <class U> friend Matrix<U> operator +(const Matrix<U> &left, const U &right);

        template <class U> friend Matrix<U> operator -(const Matrix<U> &left, const Matrix<U> &right);
        template <class U> friend Matrix<U> operator -(const U &left, const Matrix<U> &right);
        template <class U> friend Matrix<U> operator -(const Matrix<U> &left, const U &right);

        template <class U> friend Matrix<U> operator *(const Matrix<U> &left, const Matrix<U> &right);
        template <class U> friend Matrix<U> operator *(const U &left, const Matrix<U> &right);
        template <class U> friend Matrix<U> operator *(const Matrix<U> &left, const U &right);
        
        template <class U> friend Matrix<U> operator ^(const Matrix<U> &base, const int &power);

        // Output method
        template <class U> friend std::ostream &operator <<(std::ostream &os, const Matrix<U> &matrix);

        private:
            int Sub2Ind(const int row, const int column) const;

        private:
            int m_nRows, m_nColumns, m_nElements;
            T *m_matrixData;

};

/*
Constructor and Destructor methods
*/

// Default
template <class T>
Matrix<T>::Matrix()
{
    m_nRows = 1; m_nColumns = 1; m_nElements = 1;
    m_matrixData = new T[m_nElements];
    *m_matrixData = T();
}


// Zero Matrix of size rows * columns
template <class T>
Matrix<T>::Matrix(const int rows, const int columns)
{
    m_nRows = rows; m_nColumns = columns, m_nElements = rows*columns;
    m_matrixData = new T[m_nElements];
    for(int i=0; i<m_nElements; ++i){*(m_matrixData + i) = T();}
}

// Matrix from const array
template <class T>
Matrix<T>::Matrix(const int rows, const int columns, const T *inputData)
{
    m_nRows = rows; m_nColumns = columns; m_nElements = rows*columns;
    m_matrixData = new T[m_nElements];
    for(int i=0; i<m_nElements; ++i){*(m_matrixData + i) = *(inputData + i);}
}

// Copy a Matrix
template <class T>
Matrix<T>::Matrix(const Matrix<T> &inputMatrix)
{
    m_nRows = inputMatrix.m_nRows;
    m_nColumns = inputMatrix.m_nColumns;
    m_nElements = inputMatrix.m_nElements;
    m_matrixData = new T[m_nElements];
    for(int i=0; i<m_nElements; ++i){*(m_matrixData + i) = *(inputMatrix.m_matrixData + i);}
}

// Destructor
template <class T>
Matrix<T>::~Matrix()
{
    if(m_matrixData)
    {
        delete[] m_matrixData;
    }
}

/*
Configuration
*/

template <class T>
bool Matrix<T>::resize(const int rows, const int columns)
{
    m_nRows = rows; m_nColumns = columns;
    m_nElements = rows * columns;
    delete[] m_matrixData;
    m_matrixData = new T[m_nElements];
    if(m_matrixData)
    {
        for(int i=0; i<m_nElements; ++i)
        {
            *(m_matrixData + i) = T();
        }
        return true;
    }
    else
    {
        return false;
    }
}

/*
Elements
*/

// Getter
template <class T>
T Matrix<T>::getEntry(const int row, const int column) const
{
    int lini = Sub2Ind(row, column);
    if(lini >= 0)
    {
        return *(m_matrixData + lini);
    }
    else
    {
        return T();
    }
}

template <class T>
int Matrix<T>::getRows() const
{
    return m_nRows;
}

template <class T>
int Matrix<T>::getColumns() const
{
    return m_nColumns;
}

// Setter
template <class T>
bool Matrix<T>::setEntry(const int row, const int column, const T value)
{
    int lini = Sub2Ind(row, column);
    if(lini >= 0)
    {
        *(m_matrixData + lini) = value;
        return true;
    }
    else
    {
        return false;
    }
}

/*
Operator overloading
*/

// Addition matrix + matrix
template <class T>
Matrix<T> operator +(const Matrix<T> &left, const Matrix<T> &right)
{
    int rows = left.m_nRows; int columns = left.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = *(left.m_matrixData + i) + *(right.m_matrixData + i);
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}

// Addition scalar + matrix
template <class T>
Matrix<T> operator +(const T &left, const Matrix<T> &right)
{
    int rows = right.m_nRows; int columns = right.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = left + *(right.m_matrixData + i);
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}

// Addition matrix + scalar
template <class T>
Matrix <T> operator +(const Matrix<T> &left, const T &right)
{
    int rows = left.m_nRows; int columns = left.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = *(left.m_matrixData + i) + right;
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}


// Subtraction matrix - matrix
template <class T>
Matrix<T> operator -(const Matrix<T> &left, const Matrix<T> &right)
{
    int rows = left.m_nRows; int columns = left.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = *(left.m_matrixData + i) - *(right.m_matrixData + i);
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}

// Subtraction scalar - matrix
template <class T>
Matrix<T> operator -(const T &left, const Matrix<T> &right)
{
    int rows = right.m_nRows; int columns = right.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = left - *(right.m_matrixData + i);
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}

// Subtraction matrix - scalar
template <class T>
Matrix <T> operator -(const Matrix<T> &left, const T &right)
{
    int rows = left.m_nRows; int columns = left.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = *(left.m_matrixData + i) - right;
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}

// Multiplication matrix * scalar
template <class T>
Matrix <T> operator *(const Matrix<T> &left, const T &right)
{
    int rows = left.m_nRows; int columns = left.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = *(left.m_matrixData + i) * right;
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}

// Multiplication scalar * matrix
template <class T>
Matrix<T> operator *(const T &left, const Matrix<T> &right)
{
    int rows = right.m_nRows; int columns = right.m_nColumns;
    int elements = rows * columns;
    T *temp = new T[elements];
    for(int i=0; i<elements; ++i)
    {
        *(temp + i) = left * *(right.m_matrixData + i);
    }
    Matrix<T> res(rows, columns, temp);
    delete[] temp;
    return res;
}


// Multiplication matrix * matrix
template <class T>
Matrix<T> operator *(const Matrix<T> &left, const Matrix<T> &right)
{
    int r_rows = right.m_nRows; int r_columns = right.m_nColumns;
    int l_rows = left.m_nRows; int l_columns = left.m_nColumns;

    if(l_columns == r_rows)
    {
        T *temp = new T[left.m_nRows * right.m_nColumns];

        for(int i=0; i<l_rows; ++i)
        {
            for(int j=0; j<r_columns; ++j)
            {
                T elem = T();
                for(int k=0; k<l_columns; ++k)
                {
                    int llini = (i * l_columns) + k;
                    int rlini = (k * r_columns) + j;

                    elem = elem + *(left.m_matrixData + llini) * *(right.m_matrixData + rlini);
                }

                int reslini = (i * r_columns) + j;
                *(temp + reslini) = elem;
            }
        }
        Matrix<T> res(l_rows, r_columns, temp);
        delete[] temp;
        return res;
    }
    else
    {
        Matrix<T> res(1,1);
        return res;
    }
}

// == Operator
template <class T>
bool Matrix<T>::operator ==(const Matrix<T> &input)
{
    if((this->m_nRows != input.m_nRows) || (this->m_nColumns != input.m_nColumns))
    {
        return false;
    }
    for(int i=0; i<this->m_nElements; ++i)
    {
        if(*(this->m_matrixData + i) != *(input.matrixData + i))
        {
            return false;
        }
    }
    return true;
}



/*
That one private function to get a linear index from a matrix subscript
*/

template <class T>
int Matrix<T>::Sub2Ind(const int row, const int column) const
{
    if((row < m_nRows) && (row >= 0) && (column < m_nColumns) && (column >= 0))
    {
        return (row * m_nColumns) + column;
    }
    else
    {
        return -1;
    }
}


// Output method
template <class T>
std::ostream &operator <<(std::ostream &os, const Matrix<T> &matrix)
{
    os << "[ ";
    for(int col=0; col<matrix.m_nColumns-1; ++col)
    {
        os << matrix.getEntry(0, col) << ", ";
    }
    os << matrix.getEntry(0, matrix.m_nColumns-1) << " ]\n";

    for(int row=1; row<matrix.m_nRows-1; ++row)
    {
        os << "| ";
        for(int col=0; col<matrix.m_nColumns-1; ++col)
        {
            os << matrix.getEntry(row, col) << ", ";
        }
        os << matrix.getEntry(row, matrix.m_nColumns-1) << " |\n";
    }

    os << "[ ";
    for(int col=0; col<matrix.m_nColumns-1; ++col)
    {
        os << matrix.getEntry(matrix.m_nRows-1, col) << ", ";
    }
    os << matrix.getEntry(matrix.m_nRows-1, matrix.m_nColumns-1) << " ]\n";
    return os;
}

#endif

