#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string.h>

#include "Komplex.h"
#include "Polynom.h"
#include "Matrix.h"


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

    return 0;
}

