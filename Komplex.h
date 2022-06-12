#ifndef KOMPLEX_H
#define KOMPLEX_H

class Komplex
{
    public:
        // Constructors
        Komplex();
        Komplex(const double real, const double img);
        Komplex(const Komplex &z);

        // Check for zero value
        bool istNull();

        // Getters and Setters
        double getReal() const;
        double getImg() const;
        void setReal(const double real);
        void setImg(const double img);

        // Equals operator
        bool operator ==(const Komplex &z) const;
        bool operator ==(const double &num) const;

        // Addition, subtraction, multiplication operators
        friend Komplex operator +(const Komplex &left, const Komplex &right);
        friend Komplex operator +(const double &left, const Komplex &right);
        friend Komplex operator +(const Komplex &left, const double &right);

        friend Komplex operator -(const Komplex &left, const Komplex &right);
        friend Komplex operator -(const double &left, const Komplex &right);
        friend Komplex operator -(const Komplex &left, const double &right);

        friend Komplex operator *(const Komplex &left, const Komplex &right);
        friend Komplex operator *(const double &left, const Komplex &right);
        friend Komplex operator *(const Komplex &left, const double &right);

        friend Komplex operator ^(const Komplex &base, const int &power);

        // Absolute value
        double abs(const Komplex &z);

        // Standard output
        friend std::ostream &operator <<(std::ostream &os, const Komplex &z);

        private:
            double real; double img;
};

/*
Constructors
*/

// Default
Komplex::Komplex()
{
    real = 0.0;
    img = 0.0;
}

// Complex numbers from given values
Komplex::Komplex(const double real, const double img)
{
    this->real = real;
    this->img = img;
}

// Copy a Complex Number
Komplex::Komplex(const Komplex &z)
{
    real = z.real;
    img = z.img;
}

/*
Check for zero
*/
bool Komplex::istNull()
{
    return (this->real == 0.0 && this->img == 0.0);
}

/*
Getters and Setters
*/
double Komplex::getReal() const
{
    return real;
}

double Komplex::getImg() const
{
    return img;
}

void Komplex::setReal(const double real)
{
    this->real = real;
}

void Komplex::setImg(const double img)
{
    this->img = img;
}

/*
Equality operators
*/
bool Komplex::operator ==(const Komplex &z) const
{
    return (this->real == z.real && this->img == z.img);
}

bool Komplex::operator ==(const double &num) const
{
    return (this->real == num && this->img == 0.0);
}

/*
Addition
*/
Komplex operator +(const Komplex &left, const Komplex &right)
{
    return Komplex(left.real + right.real, left.img + right.img);
}

Komplex operator +(const double &left, const Komplex &right)
{
    return Komplex(left + right.real, right.img);
}

Komplex operator +(const Komplex &left, const double &right)
{
    return Komplex(left.real + right, left.img);
}

/*
Subtraction
*/
Komplex operator -(const Komplex &left, const Komplex &right)
{
    return Komplex(left.real - right.real, left.img - right.img);
}

Komplex operator -(const double &left, const Komplex &right)
{
    return Komplex(left - right.real, right.img);
}

Komplex operator -(const Komplex &left, const double &right)
{
    return Komplex(left.real - right, left.img);
}

/*
Multiplication
*/
Komplex operator *(const Komplex &left, const Komplex &right)
{
    return Komplex(left.real*right.real - left.img*right.img, left.real*right.img + left.img*right.real);
}

Komplex operator *(const double &left, const Komplex &right)
{
    return Komplex(left * right.real, left * right.img);
}

Komplex operator *(const Komplex &left, const double &right)
{
    return Komplex(left.real * right, left.img * right);
}


/*
Exponentiation
*/
Komplex operator ^(const Komplex &base, const int &power)
{
    if(power == 0)
    {
        return Komplex();
    }

    Komplex res(base.real, base.img);
    for(int i=0; i<power; ++i)
    {
        res = res * res;
    }
    return res;
}

// Absolute value
double Komplex::abs(const Komplex &z)
{
    return sqrt(z.real*z.real + z.img * z.img);
}

// Output method
std::ostream &operator <<(std::ostream &os, const Komplex &z)
{
    os << z.real;
    if(z.img != 0.0)
    {
        if(z.img < 0)
        {
            os << " - ";
        }
        else
        {
            os << " + ";
        }
        os << z.img << "i";
    }
    return os;
}

#endif

