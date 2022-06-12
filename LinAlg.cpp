#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string.h>

#include "Komplex.h"
#include "Polynom.h"
#include "Matrix.h"


Matrix<Komplex> id(const int size)
{
    Matrix<Komplex> res(size, size);
    Komplex z(1, 0);
    for(int i=0; i<size; ++i)
    {
        res.setEntry(i, i, z);
    }
    return res;
}


/*
Calculates the derivative function of a polynomial with complex coefficients.
*/
Polynom<Komplex> ableitungsfunktion(const Polynom<Komplex> &f)
{
    int deg = f.getDegree();
    if(deg == 0)
    {
        Komplex coef;
        Polynom<Komplex> res(coef);
        return res;
    }
    Komplex *reslist = new Komplex[deg];
    for(int i=1; i<=deg; ++i)
    {
        *(reslist + i - 1) = (i-1) * f.getCoefficient(i);
    }
    Polynom<Komplex> res(deg, reslist);
    delete[] reslist;
    return res;
}

/*
Calculates the value of a polynomial with complex coefficients at the given value.
*/
Komplex einsetzen(const Polynom<Komplex> &f, const Komplex &z)
{
    Komplex res;
    for(int i=0; i<=f.getDegree(); ++i)
    {
        res = res + f.getCoefficient(i) * z^(i-1);
    }
    return res;
}

Komplex einsetzen(const Polynom<Komplex> &f, const double &num)
{
    Komplex res;
    for(int i=0; i<=f.getDegree(); ++i)
    {
        res = res + f.getCoefficient(i) * num^(i-1);
    }
    return res;
}


int main()
{
    Komplex a;
    Komplex b(1, 1);
    Komplex c(2.5, 3.5);
    Komplex d = a + b;
    Komplex e = a * d;

    std::cout << a << "\n" << b << "\n" << c << "\n" << d << "\n";

    Komplex coefs[4] = {d, d, a, d};
    Polynom<Komplex> f(4, coefs);

    std::cout << f << "\n";

    int data[16] = {1, 2, 3, 4, 2, 2, 3, 4, 3, 3, 3, 4, 4, 4, 4, 4};
    Matrix<int> M(4, 4, data);

    std::cout << M << "\n";

    Matrix<Komplex> A = id(5);

    std::cout << A << "\n";

    return 0;
}

