#include <cmath>

#include <complex>
#include <iostream>
#include <iomanip>
#include <algorithm>

typedef std::complex< long > cpx;

// ********************************************
//
//

long gcd( long a, long b ) {
    if ( b == 0 ) return a;
    a %= b;
    return gcd( b, a );
}

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
/*
    bool operator< ( const ComplexFraction &rhs );
    bool operator> ( const ComplexFraction &rhs );
    bool operator==( const ComplexFraction &rhs );
    bool operator<=( const ComplexFraction &rhs );
    bool operator>=( const ComplexFraction &rhs );
*/
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

ComplexFraction ComplexFraction::reduce() {
    ComplexFraction f = *this;
    // long a[3], num;
    // a[0] + a[1]i
    // ------------
    //     a[2]
    /*
    a[0] = (this->numer).real();
    a[1] = (this->numer).imag();
    a[2] = (this->denom).real();
    std::sort(a, a+3);
    num = gcd( a[2], gcd(a[1], a[0]) );
    if ( num != 1 ) {
        f.numer = cpx( a[0]/num, a[1]/num );
        f.denom = cpx( a[2]/num,     0    );
    }
    */
    long a, b, c, num;
    a = (this->numer).real();
    b = (this->numer).imag();
    c = (this->denom).real();
    num = gcd(abs(a), gcd(abs(b), abs(c)));
    if ( num != 1 ) {
        f.numer = cpx( a/num, b/num );
        f.denom = cpx( c/num,   0   );
    }
    return f;
}

ComplexFraction ComplexFraction::rationarize() {
    ComplexFraction f;
    if ( (this->denom).imag() != 0 ) {
        f.denom = (this->denom) * std::conj( this->denom );
        f.numer = (this->numer) * std::conj( this->denom );
    } else {
        f.denom = this->denom;
        f.numer = this->numer;
    }
    f = f.reduce();
    if ( (f.denom).real() < 0 ) {
        f.denom = cpx( -(f.denom).real(), 0 );
        f.numer = cpx( -(f.numer).real(), -(f.numer).imag() );
    }
    return f;
}

ComplexFraction ComplexFraction::conjugate() {
    ComplexFraction f;
    if ( (this->denom).imag() != 0 ) {
        f = this->rationarize();
    } else {
        f = *this;
    }
    f.numer = std::conj( f.numer );
    return f;
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


ComplexFraction ComplexFraction::operator-( const ComplexFraction &rhs ) {
    ComplexFraction x;
    cpx n, d;
    if (this->denom != rhs.denom) {
        d = this->denom * rhs.denom;
        n = (this->numer * rhs.denom) - (this->denom * rhs.numer);
    } else {
        d = this->denom;
        n = this->numer + rhs.numer;
    }
    x = ComplexFraction(n, d);
    return x.rationarize();
}

void ComplexFraction::print() {
    std::string nsgn = ( (this->numer).imag() < 0 ) ? " - " : " + ",
                dsgn = ( (this->denom).imag() < 0 ) ? " - " : " + ";
    std::cout << std::setw(  5 ) << (this->numer).real() << nsgn
              << std::setw(  5 ) << abs( (this->numer).imag() ) << "i\n"
              << std::setw( 15 ) << std::setfill('-')    << '\n'
              << std::setfill(' ');
    if ( (this->denom).imag() != 0 ) {
        std::cout << std::setw( 5 ) << (this->denom).real() << dsgn
                  << std::setw( 5 ) << abs( (this->denom).imag() ) <<"i\n\n";
    } else {
        std::cout << std::setw( 8 ) << (this->denom).real() << "\n\n";
    }
}

int main() {
    cpx a(1, 2), b(1, -2);
    ComplexFraction f = ComplexFraction(a, b);
    ComplexFraction g = ComplexFraction(b, a);
    (f+g).print();
    return 0;
}
