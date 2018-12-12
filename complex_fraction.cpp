#include <cmath>

#include <complex>
#include <iostream>

typedef std::complex< long > cpx;

// ********************************************
//
//

class ComplexFraction {
private:
    cpx numer; // numerator
    cpx denom; // denominator
public:
    ComplexFraction();
    ComplexFraction( cpx n, cpx d );
    ~ComplexFraction();

    ComplexFraction operator+( const ComplexFraction &rhs );
    ComplexFraction operator-( const ComplexFraction &rhs );

    bool operator< ( const ComplexFraction &rhs );
    bool operator> ( const ComplexFraction &rhs );
    bool operator==( const ComplexFraction &rhs );
    bool operator<=( const ComplexFraction &rhs );
    bool operator>=( const ComplexFraction &rhs );

    ComplexFraction conjugate();
    ComplexFraction rationarize();
    ComplexFraction reduce();

    void print();
};


ComplexFraction::ComplexFraction() {
    numer = cpx(1, 0);
    denom = cpx(1, 0);
}

ComplexFraction::ComplexFraction( cpx n, cpx d ) {
    numer = n;
    denom = d;
}

ComplexFraction::~ComplexFraction() {  }

ComplexFraction ComplexFraction::rationarize() {

}

ComplexFraction ComplexFraction::operator+( const ComplexFraction &rhs ) {
    ComplexFraction x;
    cpx n, d;
    if (this->denom != rhs.denom) {
        d = this->denom * rhs.denom;
        n = (this->numer * rhs.denom) + (this->denom * rhs.numer);
    } else {
        d = this->denom;
        n = this->numer + rhs.numer;
    }
    x = ComplexFraction(n, d);
    return x.rationarize();
}

int main() {
    ComplexFraction f;
    cpx a(1, 2), b(1, -2);
    std::cout << a*b<< std::endl;
    return 0;
}
