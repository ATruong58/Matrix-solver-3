//Default Constructor
template <typename T>
denseMatrix<T>::denseMatrix()
{
    m_matrix = myvector<myvector<T> >(3);

    for(int i = 0; i < 3; i++)
    {
        m_matrix[i] = myvector<T>(3); 
    }

    m_column_size = 3;
    m_row_size = 3;
}

//Paramitized Constructor
template <typename T>
denseMatrix<T>::denseMatrix(const int column_size, const int row_size)
{
    m_matrix = myvector<myvector<T> >(column_size);

    for(int i = 0; i < column_size; i++)
    {
        m_matrix[i] = myvector<T>(row_size); 
    }

    m_column_size = column_size;
    m_row_size = row_size;
}

//Copy Constructor
template <typename T>
denseMatrix<T>::denseMatrix(const denseMatrix &source)
{
    m_matrix = myvector<myvector<T> >(source.m_column_size);

    for(int i = 0; i < source.m_column_size; i++)
    {
        m_matrix[i] = source[i];
    }

    m_column_size = source.m_column_size;
    m_row_size = source.m_row_size;
}

//Operator = 
template <typename T>
denseMatrix<T>& denseMatrix<T>::operator=(const denseMatrix<T> &source)
{
    m_matrix = myvector<myvector<T> >(source.m_column_size);

    for(int i = 0; i < source.m_column_size; i++)
    {
        m_matrix[i] = source[i];
    }

    m_column_size = source.m_column_size;
    m_row_size = source.m_row_size;

    return *this;

}

//Operator = (move constructor)
template <typename T>
denseMatrix<T>& denseMatrix<T>::operator=(denseMatrix<T> &&source)
{
    m_matrix = myvector<myvector<T> >(source.m_column_size);

    m_matrix = std::move(source.m_matrix);

    m_column_size = source.m_column_size;
    m_row_size = source.m_row_size;

    return *this;

}

//Binary + between 2 matrixs
template <typename T>
denseMatrix<T> denseMatrix<T>::operator+(const denseMatrix<T> &rhs)const
{
    denseMatrix<T> temp(m_column_size, m_row_size);
    
    if(m_column_size == rhs.m_column_size && m_row_size == rhs.m_row_size)
        {
        for(int i = 0; i < m_column_size; i++)
        {
            temp[i] = m_matrix[i] + rhs.m_matrix[i];
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary + between a denseMatrix and a upperMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator+(const upperMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            for(int j = i; j < rhs.getSize(); j++)
            {
                if(i <= j)
                {
                    temp[i][j] = temp[i][j] + rhs(i,j);
                }
            }
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary + between a denseMatrix and a lowerMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator+(const lowerMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            for(int j = 0; j < i+1; j++)
            {
                if(i >= j)
                {
                    temp[i][j] = temp[i][j] + rhs(i,j);
                }
            }
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary + between a denseMatrix and a diagonalMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator+(const diagonalMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            temp[i][i] = temp[i][i] + rhs[0][i];
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary + between a denseMatrix and a tridiagonalMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator+(const tridiagonalMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {
            for(int j = 0; j < rhs.getSize(); j++)
            {
                if(i <= j + 1 || i >= j - 1 || i == j)
                {
                    temp[i][j] = temp[i][j] + rhs(i,j);
                }
            }   
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary + between a denseMatrix and a symmetricrMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator+(const symmetricMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            for(int j = 0; j < rhs.getSize(); j++)
            {
                temp[i][j] = temp[i][j] + rhs(i,j);
            }
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary - between 2 matrixs
template <typename T>
denseMatrix<T> denseMatrix<T>::operator-(const denseMatrix<T> &rhs)const
{
    denseMatrix<T> temp(m_column_size, m_row_size);
    
    if(m_column_size == rhs.m_column_size && m_row_size == rhs.m_row_size)
    {
        for(int i = 0; i < m_column_size; i++)
        {
            temp[i] = m_matrix[i] - rhs.m_matrix[i];
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary - between a denseMatrix and a upperMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator-(const upperMatrix<T> &rhs)const
{
    denseMatrix<T> temp(*this);
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            for(int j = i; j < rhs.getSize(); j++)
            {
                if(i <= j)
                {
                    temp[i][j] = temp[i][j] - rhs(i,j);
                }
            }
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary - between a denseMatrix and a lowerMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator-(const lowerMatrix<T> &rhs)const
{
    denseMatrix<T> temp(*this);
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            for(int j = 0; j < i+1; j++)
            {
                if(i >= j)
                {
                    temp[i][j] = temp[i][j] - rhs(i,j);
                }
            }
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary - between a denseMatrix and a diagonalMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator-(const diagonalMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            temp[i][i] = temp[i][i] - rhs[0][i];
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary - between a denseMatrix and a tridiagonalMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator-(const tridiagonalMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {
            for(int j = 0; j < rhs.getSize(); j++)
            {
                if(i <= j + 1 || i >= j - 1 || i == j)
                {
                    temp[i][j] = temp[i][j] - rhs(i,j);
                }
            }   
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary - between a denseMatrix and a symmetricrMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator-(const symmetricMatrix<T> &rhs)const
{
    denseMatrix<T> temp = *this;
    
    if(m_column_size == rhs.getSize() && m_row_size == rhs.getSize())
    {
        for(int i = 0; i < rhs.getSize(); i++)
        {   
            for(int j = 0; j < rhs.getSize(); j++)
            {
                temp[i][j] = temp[i][j] - rhs(i,j);
            }
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary * between 2 matrixs
template <typename T>
denseMatrix<T> denseMatrix<T>::operator*(const denseMatrix<T> &rhs)const
{
    denseMatrix<T> temp(m_column_size, rhs.m_row_size);
    denseMatrix<T> transpose = rhs.transpose();
    
    if(m_row_size == rhs.m_column_size)
    {

        for(int i = 0; i < m_column_size; i++)
        {
            for(int j = 0; j < rhs.m_row_size; j++)
            {
                temp[i][j] = m_matrix[i] * transpose[j];
            }    
        }

    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;

}

//Binary * between a denseMatrix and a upperMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator*(const upperMatrix<T> &rhs)const
{
    denseMatrix<T> temp(m_column_size, rhs.getSize());

    if(m_row_size == rhs.getSize())
    {

        for(int i = 0; i < m_column_size; i++)
        {
            for(int j = 0; j < rhs.getSize(); j++)
            {   
                for(int k = 0; k < rhs.getSize(); k++)
                {
                    if(k <= j)
                    {
                        temp[i][j] = temp[i][j] + (m_matrix[i][k] * rhs(k,j));
                    }
                }
            }
            
        }

    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;

}

//Binary * between a denseMatrix and a lowerMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator*(const lowerMatrix<T> &rhs)const
{
    denseMatrix<T> temp(m_column_size, rhs.getSize());

    if(m_row_size == rhs.getSize())
    {
        for(int i = 0; i < m_column_size; i++)
        {
            for(int j = 0; j < rhs.getSize(); j++)
            {   
                for(int k = 0; k < rhs.getSize(); k++)
                {
                    if(k >= j)
                    {
                        temp[i][j] = temp[i][j] + (m_matrix[i][k] * rhs(k,j));
                    }
                }
            }
            
        }
    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;

}

//Binary * between a denseMatrix and a diagonalMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator*(const diagonalMatrix<T> &rhs)const
{
    denseMatrix<T> temp(*this);

    if(m_row_size == rhs.getSize())
    {

        for(int i = 0; i < m_column_size; i++)
        {
            for(int j = 0; j < rhs.getSize(); j++)
            {  
                temp[j][i] = temp[j][i] * rhs[0][i];
            }
            
        }

    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;

}

//Binary * between a denseMatrix and a tridiagonalMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator*(const tridiagonalMatrix<T> &rhs)const
{
    denseMatrix<T> temp(m_column_size, rhs.getSize());

    if(m_row_size == rhs.getSize())
    {

        for(int i = 0; i < m_column_size; i++)
        {
            for(int j = 0; j < rhs.getSize(); j++)
            {  
                for(int k = 0; k < rhs.getSize(); k++)
                {
                    if(i <= k + 1 || i >= k - 1 || i == k)
                    {
                        temp[i][j] =  temp[i][j] + (m_matrix[i][k] * rhs(k,j));
                    }
                }
            }
            
        }

    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;
}

//Binary * between a symmetricMatrix and a symmetricMatrix
template <typename T>
denseMatrix<T> denseMatrix<T>::operator*(const symmetricMatrix<T> &rhs)const
{
    denseMatrix<T> temp(m_column_size, rhs.getSize());
    
    if(m_row_size == rhs.getSize())
    {

        for(int i = 0; i < m_column_size; i++)
        {
            for(int j = 0; j < rhs.getSize(); j++)
            {  
                for(int k = 0; k < rhs.getSize(); k++)
                {
                    temp[i][j] =  temp[i][j] + (m_matrix[i][k] * rhs(k,j));
                }
            }

        }

    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;

}

//Binary * between a matrix and a vector
template <typename T>
myvector<T> denseMatrix<T>::operator*(const myvector<T> &rhs)const
{
    myvector<T> temp(m_column_size);
    
    if(m_row_size == rhs.getSize())
    {
        
        for(int i = 0; i < m_column_size; i++)
        {
            temp[i] = m_matrix[i] * rhs;
        }

    }
    else
    {
        throw std::out_of_range( "Size not equal");
    }

    return temp;


}

//Scalar multiplication
template <typename T>
denseMatrix<T> denseMatrix<T>::operator*(const int scale)const
{
    denseMatrix<T> temp(m_column_size, m_row_size);
    
    for(int i = 0; i < m_column_size; i++)
    {
        temp[i] = m_matrix[i] * scale;
    }

    return temp;
}

//Operator []
template <typename T>
myvector<T> denseMatrix<T>::operator[](int index)const
{
    if(m_column_size >= index)
    {
        return m_matrix[index];
    }
    else
    {
        throw std::out_of_range( "Index out of bounds");
    }
}

//Operator [] with reference
template <typename T>
myvector<T>& denseMatrix<T>::operator[](int index)
{
    if(m_column_size>= index)
    {
        return m_matrix[index];
    }
    else
    {
        throw std::out_of_range( "Index out of bounds");
    }
}

//Transpose function
template <typename T>
denseMatrix<T> denseMatrix<T>::transpose()const
{
    denseMatrix temp(m_row_size, m_column_size);

    for(int i = 0; i < m_row_size; i++)
    {
        for(int j = 0; j < m_column_size; j++)
        {
            temp[i][j] = m_matrix[j][i];
        }
    }

    return temp;

}

//Getter for m_column_size
template <typename T>
int denseMatrix<T>::getColumnSize()const
{
    return m_column_size;
}

//Getter for m_row_size
template <typename T>
int denseMatrix<T>::getRowSize()const
{
    return m_row_size;
}

//Check if matrix is upper
template <typename T>
bool denseMatrix<T>::isUpper()const
{
    for(int i = 0; i < m_column_size; i++)
    {
        for(int j = 0; j < m_row_size; j++)
        {
            if(i == j && m_matrix[i][j] == 0)
            {
                return false;
            }

            if(i > j && m_matrix[i][j] != 0)
            {
                return false;
            }
        }
    }

    return true;
}

//Check if matrix is lower
template <typename T>
bool denseMatrix<T>::isLower()const
{
    for(int i = 0; i < m_column_size; i++)
    {
        for(int j = 0; j < m_row_size; j++)
        {
            if(i == j && m_matrix[i][j] == 0)
            {
                return false;
            }

            if(i < j && m_matrix[i][j] != 0)
            {
                return false;
            }
        }
    }

    return true;
}

//Check if matrix is upper
template <typename T>
upperMatrix<T> denseMatrix<T>::toUpper()const
{
    if(m_column_size != m_row_size)
    {
        throw std::out_of_range( "Not a square matrix");
    }
    
    upperMatrix<T> temp(m_column_size);

    for(int i = 0; i < m_column_size; i++)
    {
        for(int j = 0; j < m_row_size; j++)
        {
            if(i <= j)
            {
                temp(i,j) = m_matrix[i][j];
            }
        }
    }

    return temp;
}

//Check if matrix is lower
template <typename T>
lowerMatrix<T> denseMatrix<T>::toLower()const
{
    if(m_column_size != m_row_size)
    {
        throw std::out_of_range( "Not a square matrix");
    }
    
    lowerMatrix<T> temp(m_column_size);

    for(int i = 0; i < m_column_size; i++)
    {
        for(int j = 0; j < m_row_size; j++)
        {
            if(i >= j)
            {
                temp(i,j) = m_matrix[i][j];
            }
        }
    }

    return temp;
}

//Output
template <typename T>
std::ostream& operator<<(std::ostream& os, const denseMatrix<T> &obj)
{
    for(int i = 0; i < obj.getColumnSize(); i++)
    {
        os << obj[i] << std::endl;
    }
    return os;  
}

//Input
template <typename T>
std::istream& operator>>(std::istream& in, denseMatrix<T> &obj)
{
    for(int i = 0; i < obj.getColumnSize(); i++)
    {
        in >> obj[i];
    }

    return in;
}
