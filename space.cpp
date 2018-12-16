#include "complex_fraction.cpp"

/*
 * let C be a complex space. then, we define
 *
 * half complex space h as follows:
 * h := { z \in C | Im z > 0 }
 *
 * and we also define a set F as follows:
 * F := { z \in h |   -1/2 <= Re z < 1/2
 *                | , |z| >= 1
 *                | , 0 < Re z < 1/2 -> |z| > 1 }
 */

bool is_in_h( ComplexFraction f ) {
    return f.imag() > 0;
}

bool is_in_F( ComplexFraction f ) {
    if ( !is_in_h( f ) ) return false;
    bool cond1, cond2, cond3;
    cond1 = f.real() >= -0.5 && f.real() < 0.5;
    cond2 = f.norm() >= 1;
    if ( 0 < f.real() && f.real() < 0.5 ) {
        cond3 = f.norm() > 1;
    } else {
        cond3 = true;
    }
    return cond1 && cond2 && cond3;
}

int main() {
    cpx a(1, -5), b(3, 0);
    ComplexFraction f = ComplexFraction(a, b);
    if ( is_in_F( f ) ) {
        std::cout << "f is in F" << std::endl;
    }
    return 0;
}
