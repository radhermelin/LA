#ifndef POLYNOM_H
#define POLYNOM_H

template <class T>
class Polynom
{
    public:
        // Constructors
        Polynom();
        Polynom(const int cNums, const T *coefs);
        Polynom(const Polynom<T> &f);

        // Destructor
        ~Polynom();

        // Getters
        T getCoefficient(const int index) const;
        int getDegree() const;

        // Equality operator
        bool operator ==(const Polynom<T> &f);

        // Addition, subtraction, multiplication
        template <class U> friend Polynom<U> operator +(const Polynom<U> &left, const Polynom<U> &right);
        template <class U> friend Polynom<U> operator +(const U &left, const Polynom<U> &right);
        template <class U> friend Polynom<U> operator +(const Polynom<U> &left, const U &right);

        template <class U> friend Polynom<U> operator +(const Polynom<U> &left, const Polynom<U> &right);
        template <class U> friend Polynom<U> operator +(const U &left, const Polynom<U> &right);
        template <class U> friend Polynom<U> operator +(const Polynom<U> &left, const U &right);

        template <class U> friend Polynom<U> operator +(const Polynom<U> &left, const Polynom<U> &right);
        template <class U> friend Polynom<U> operator +(const U &left, const Polynom<U> &right);
        template <class U> friend Polynom<U> operator +(const Polynom<U> &left, const U &right);

        // Output method
        template <class U> friend std::ostream &operator <<(std::ostream &os, const Polynom<U> &f);

        private:
            int degree;
            T *coefficients;
};

/*
Constructors and Destructor
*/

// Zero polynomial
template <class T>
Polynom<T>::Polynom()
{
    degree = 0;
    coefficients = new T[1];
    *coefficients = T();
}

// Polynomial from coefficients
template <class T>
Polynom<T>::Polynom(const int cNums, const T *coefs)
{
    degree = cNums-1;
    while(degree > 0 && *(coefs + degree) == 0.0){degree -= 1;}
    coefficients = new T[degree+1];
    for(int i=0; i<=degree; ++i){*(coefficients + i) = *(coefs + i);}
}

// Copy a polynomial
template <class T>
Polynom<T>::Polynom(const Polynom<T> &f)
{
    degree = f.degree;
    for(int i=0; i<=degree; ++i){*(coefficients + i) = *(f.coefficients + i);}
}

// Destroy a polynomial
template <class T>
Polynom<T>::~Polynom()
{
    if(coefficients)
    {
        delete[] coefficients;
    }
}

/*
Getters
*/
template <class T>
T Polynom<T>::getCoefficient(const int index) const
{
    if(index <= this->degree)
    {
        return *(this->coefficients + index);
    }
    else
    {
        return T();
    }
}

template <class T>
int Polynom<T>::getDegree() const
{
    return this->degree;
}

/*
Equality operator
*/
template <class T>
bool Polynom<T>::operator ==(const Polynom<T> &f)
{
    if(this->degree != f.degree)
    {
        return false;
    }

    for(int i=0; i<=this->degree; ++i)
    {
        if(*(this->coefficients + i) != *(f.coefficients + i))
        {
            return false;
        }
    }
    return true;
}

/*
Addition
*/
template <class T>
Polynom<T> operator +(const Polynom<T> &left, const Polynom<T> &right)
{
    int deg = (left.degree < right.degree) ? right.degree : left.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=left.degree; ++i)
    {
        *(temp + i) = *(left.coefficients + i);
    }
    for(int i=0; i<=right.degree; ++i)
    {
        *(temp + i) = *(temp + i) + *(right.coefficients + i);
    }
    Polynom<T> res(deg+1, temp);
    delete[] temp;
    return res;
}

template <class T>
Polynom<T> operator +(const T &left, const Polynom<T> &right)
{
    int deg = right.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=deg; ++i)
    {
        *(temp + i) = *(right.coefficients + i);
    }
    *(temp + deg) = *(temp + deg) + left;
    Polynom <T> res(deg+1, temp);
    delete[] temp;
    return res;
}

template <class T>
Polynom<T> operator +(const Polynom<T> &left, const T &right)
{
    int deg = left.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=deg; ++i)
    {
        *(temp + i) = *(left.coefficients + i);
    }
    *(temp + deg) = *(temp + deg) + right;
    Polynom<T> res(deg+1, temp);
    delete[] temp;
    return res;
}

/*
Subtraction
*/
template <class T>
Polynom<T> operator -(const Polynom<T> &left, const Polynom<T> &right)
{
    int deg = (left.degree < right.degree) ? right.degree : left.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=left.degree; ++i)
    {
        *(temp + i) = *(left.coefficients + i);
    }
    for(int i=0; i<=right.degree; ++i)
    {
        *(temp + i) = *(temp + i) - *(right.coefficients + i);
    }
    Polynom<T> res(deg+1, temp);
    delete[] temp;
    return res;
}

template <class T>
Polynom<T> operator -(const T &left, const Polynom<T> &right)
{
    int deg = right.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=deg; ++i)
    {
        *(temp + i) = -(*(right.coefficients + i));
    }
    *(temp + deg) = *(temp + deg) + left;
    Polynom <T> res(deg+1, temp);
    delete[] temp;
    return res;
}

template <class T>
Polynom<T> operator -(const Polynom<T> &left, const T &right)
{
    int deg = left.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=deg; ++i)
    {
        *(temp + i) = *(left.coefficients + i);
    }
    *(temp + deg) = *(temp + deg) - right;
    Polynom<T> res(deg+1, temp);
    delete[] temp;
    return res;
}

/*
Multiplication
*/
template <class T>
Polynom<T> operator *(const Polynom<T> &left, const Polynom<T> &right)
{
    int deg = left.degree+right.degree;
    T *temp = new T[deg+1];

    for(int i=0; i<=left.degree; ++i)
    {
        for(int j=0; j<=right.degree; ++j)
        {
            *(temp + j + i) = *(temp + j + i) + *(left.coefficients + i) * *(right.coefficients + j);
        }
    }

    Polynom<T> res(deg+1, temp);
    delete[] temp;
    return res;
}

template <class T>
Polynom<T> operator *(const T &left, const Polynom<T> &right)
{
    int deg = right.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=deg; ++i)
    {
        *(temp + i) = left * *(right.coefficients + i);
    }
    Polynom <T> res(deg+1, temp);
    delete[] temp;
    return res;
}

template <class T>
Polynom<T> operator *(const Polynom<T> &left, const T &right)
{
    int deg = left.degree;
    T *temp = new T[deg+1];
    for(int i=0; i<=deg; ++i)
    {
        *(temp + i) = right * *(left.coefficients + i);
    }
    Polynom<T> res(deg+1, temp);
    delete[] temp;
    return res;
}

// Output method
template <class T>
std::ostream &operator <<(std::ostream &os, const Polynom<T> &f)
{
    int deg = f.degree;

    if(deg == 0)
    {
        os << f.getCoefficient(0);
    }
    else if(deg == 1)
    {
        os << "(" << f.getCoefficient(1) << ")x";
        if(!(f.getCoefficient(0) == 0.0))
        {
            os << " + (" << f.getCoefficient(0) << ")";
        }
    }
    else
    {
        os << "(" << f.getCoefficient(deg) << ")x^" << deg;
        for(int i=deg-1; i>=2; --i)
        {
            if(f.getCoefficient(i) == 0.0)
            {
                continue;
            }
            os << " + (" << f.getCoefficient(i) << ")x^" << i;
        }
        if(!(f.getCoefficient(1) == 0.0))
        {
            os << " + (" << f.getCoefficient(1) << ")x";
        }
        if(!(f.getCoefficient(0) == 0.0))
        {
            os << " + (" << f.getCoefficient(0) << ")";
        }
    }
    return os;
}


#endif
