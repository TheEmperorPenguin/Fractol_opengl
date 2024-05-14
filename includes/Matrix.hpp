/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-14 13:57:28                                       *
*******************************************************************************/

#ifndef MATRIX_HPP
    #define MATRIX_HPP

    #include "ArcticFeather.hpp"
    #include <type_traits>
    
    template <typename T>
    class Matrix
    {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        public:
            Matrix( unsigned int size )   //Create an identiy matrix of size x size
            {
                if (size == 0)
                    throw(MatrixTooSmall());
                this->rows = size;
                this->columns = size;
                for(unsigned int x = 0; x < size; x++)
                {
                    for(unsigned int y = 0; y < size; y++)
                    {
                        if (x == y)
                            this->data.push_back(T(1));
                        else
                            this->data.push_back(T(0));
                    }
                }
            }
            unsigned int    getRows()                                   const   {return this->rows;}
            unsigned int    getColumns()                                const   {return this->columns;}
            std::vector<T>  getData()                                   const   {return this->data;}
            T               getValue(unsigned int x, unsigned int y)    const
            {
                if (y >= this->rows || x >= this->columns)
                    throw(MatrixOutOfBound());
                return this->data[this->rows * x + y];
            }
            T               setValue(T input, unsigned int x, unsigned int y)
            {
                if (y >= this->rows || x >= this->columns)
                    return (1);
                this->data[this->rows * x + y] = input;
                return (0);
            }
            Matrix( unsigned int col, unsigned int row ) //Create a matrix of size columns x rows filled with default value of T
            {
                if (row == 0 || col == 0)
                    throw(MatrixTooSmall());
                this->rows = row;
                this->columns = col;
                for(unsigned int x = 0; x < col; x++)
                {
                    for(unsigned int y = 0; y < row; y++)
                    {
                        this->data.push_back(T(0));
                    }
                }
            }                       
            Matrix( std::vector<T> input, unsigned int col, unsigned int row )      //Create a matrix of size columns x rows with input and by filling by rows
            {
                if (row == 0 || col == 0)
                    throw(MatrixTooSmall());
                unsigned int size = input.size();
                this->rows = row;
                this->columns = col;
                for(unsigned int x = 0; x < col; x++)
                {
                    for(unsigned int y = 0; y < row; y++)
                    {
                        if (col * y + x < size)
                            this->data.push_back(input[col * y + x]);
                        else
                             this->data.push_back(T(0));
                    }
                }
            }
            ~Matrix( void ){}
            Matrix( const Matrix & t )
            {
                if (this == &t)
		            return ;
                *this = t;
            }
            Matrix  &operator =( const Matrix & t )
            {
                if (this == &t)
		            return (*this);
                unsigned int row = t.getRows();
                unsigned int col = t.getColumns();
                std::vector<T> copy = t.getData();
                std::vector<T> input;
                if (row == 0 || col == 0)
                    throw(MatrixTooSmall());
                this->rows = row;
                this->columns = col;
                for(unsigned int x = 0; x < col; x++)
                {
                    for(unsigned int y = 0; y < row; y++)
                    {
                        input.push_back(copy[row * x + y]);
                    }
                }
                this->data = input;
                return (*this);
            }
            Matrix  &operator +( const Matrix & t ) const
            {
                if (this->columns != t.columns || this->rows != t.rows)
                    return (*this);
                Matrix result(*this);
                for(unsigned int x = 0; x < this->columns; x++)
                {
                    for(unsigned int y = 0; y < this->rows; y++)
                    {
                        result->setValue(this->getValue(x, y) + t.getValue(x, y), x, y);
                    }
                }
                return (*result);
            }
            Matrix  &operator +=( const Matrix & t )
            {
                if (this->columns != t.columns || this->rows != t.rows)
                    return (*this);
                for(unsigned int x = 0; x < this->columns; x++)
                {
                    for(unsigned int y = 0; y < this->rows; y++)
                    {
                        this->setValue(this->getValue(x, y) + t.getValue(x, y), x, y);
                    }
                }
                return (*this);
            }
            Matrix  &operator -( const Matrix & t ) const
            {
                if (this->columns != t.columns || this->rows != t.rows)
                    return (*this);
                for(unsigned int x = 0; x < this->columns; x++)
                {
                    for(unsigned int y = 0; y < this->rows; y++)
                    {
                        this->setValue(this->getValue(x, y) - t.getValue(x, y), x, y);
                    }
                }
                return (*this);
            }
            Matrix  &operator -=( const Matrix & t )
            {
                if (this->columns != t.columns || this->rows != t.rows)
                    return (*this);
                for(unsigned int x = 0; x < this->columns; x++)
                {
                    for(unsigned int y = 0; y < this->rows; y++)
                    {
                        this->setValue(this->getValue(x, y) - t.getValue(x, y), x, y);
                    }
                }
                return (*this);
            }
            Matrix  &operator *( const Matrix & t ) const
            {
                T sum;
                if (this->getRows() != t.getColumns())
                    return (*this);
                Matrix<T> result(this->getRows(), t.getColumns());
                for (unsigned int x = 0; x < this->getRows(); x++) {
                    for (unsigned int y = 0; y < t.getColumns(); y++) {
                        sum = 0;
                        for (unsigned int k = 0; k < this->getColumns(); k++) {
                            sum += this->getValue(k, x) * t.getValue(y, k);
                        }
                        result.setValue(sum, y, x);
                    }
                }
                *this = result;
                return (*this);
            }
            Matrix  &operator *=( const Matrix & t ) const
            {
                T sum;
                if (this->getRows() != t.getColumns())
                    return (*this);
                Matrix<T> result(this->getRows(), t.getColumns());
                for (unsigned int x = 0; x < this->getRows(); x++) {
                    for (unsigned int y = 0; y < t.getColumns(); y++) {
                        sum = 0;
                        for (unsigned int k = 0; k < this->getColumns(); k++) {
                            sum += this->getValue(k, x) * t.getValue(y, k);
                        }
                        result.setValue(sum, y, x);
                    }
                }
                *this = result;
                return (*this);
            }
            Matrix  operator *( T a ) const
            {
                Matrix result(*this);
                for(unsigned int x = 0; x < this->columns; x++)
                {
                    for(unsigned int y = 0; y < this->rows; y++)
                    {
                        result.setValue(this->getValue(x, y) * a, x, y);
                    }
                }
                return (result);
            }
            Matrix  &operator *=( T a ) const
            {
                for(unsigned int x = 0; x < this->columns; x++)
                {
                    for(unsigned int y = 0; y < this->rows; y++)
                    {
                        this->setValue(this->getValue(x, y) * a, x, y);
                    }
                }
                return (*this);
            }
        void  transpose()
        {
            if (this->rows != this->columns)
                return;
            else
            {

                std::vector<T> input;
                for(unsigned int x = 0; x < this->rows; x++)
                {
                    for(unsigned int y = 0; y < this->columns; y++)
                    {
                        input.push_back(this->data[this->rows * y + x]);
                    }
                }
                this->data = input;
                unsigned int tmp = this->rows;
                this->rows = this->columns;
                this->columns = tmp;
            }
        }
        protected:
            unsigned int    rows;
            unsigned int    columns;
            std::vector<T>  data;

        class MatrixOutOfBound : public std::exception
		{
			public:
				virtual const char* what() const throw ();
		};
        class MatrixTooSmall : public std::exception
		{
			public:
				virtual const char* what() const throw ();
		};


    };

    template <typename T>
    const char* Matrix<T>::MatrixOutOfBound::what() const throw ()
    {
        return "Matrix::OutOfBond";
    }

    template <typename T>
    const char* Matrix<T>::MatrixTooSmall::what() const throw ()
    {
        return "Matrix::TooSmall";
    }

    template <typename T>
    int getElementWidth(const T& element) {
        std::ostringstream oss;
        oss << element;  // Convert element to string representation
        return oss.str().size();  // Get the length of the resulting string
    }   

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
    {
        if (mat.getRows() - 1 != 0)
            os << "⎡";
        int width   = 1;
        int tmp     = 0;
        for(unsigned int x = 0; x < mat.getRows(); x++)
        {
            for(unsigned int y = 0; y < mat.getColumns(); y++)
            {
                tmp = getElementWidth(mat.getData()[mat.getRows() * y + x]);
                if (tmp > width)
                    width = tmp;
            }
        }
        for(unsigned int x = 0; x < mat.getRows(); x++)
        {
            if (x == mat.getRows() - 1)
                os << "⎣";
            else if (x != 0)
                os << "⎢";
            for(unsigned int y = 0; y < mat.getColumns(); y++)
            {
                os << std::setw(width) << mat.getData()[mat.getRows() * y + x];
                if (y != mat.getColumns() - 1)
                    os << std::setw(1) << " ";
            }
            if (x == 0)
                os << "⎤" << std::endl;
            else if (x == mat.getRows() - 1 && x != 0)
                os << "⎦";
            else if (x != mat.getRows() - 1)
                os << "⎥" << std::endl;
        }
        return os;
    }
    

#endif