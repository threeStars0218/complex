#include "./complex_fraction.cpp"

#include <queue>
#include <vector>
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

typedef struct _coefficient{
    long A, B, C, D;
} coefficient;

bool is_in_h( ComplexFraction f ) {
    return f.imag() >= 0;
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


std::queue< coefficient > get_coefficients( long D ) {
    long A, B, C;
    // double a = -sqrt( (double) - D / 3 );
    std::queue< coefficient > que;
    while ( !que.empty() ) { que.pop(); }
    A = sqrt( (double) - D / 3 );
    while ( A > 0 ) {
        for (B=A; B>-A; --B) {
            double c = (double) ( B*B - D ) / ( 4*A );
            // std::cout << "c = " << c << " (int) c = " << (int) c << std::endl;
            if ( c == (int) c ) {
                C = ( B*B - D ) / ( 4*A );
                if( gcd( A, gcd( abs(B), abs(C) ) ) == 1 ) {
                    /*
                    std::cout << "A = " << A << '\n'
                              << "B = " << B << '\n'
                              << "C = " << C << '\n';
                    */
                    coefficient tmp = {.A=A, .B=B, .C=C, .D=D};
                    que.push( tmp );
                }
            }
        }
        --A;
    }
    return que;
}

ComplexFraction solution( coefficient coef ) {
    cpx numer = cpx( - coef.B, -coef.D ),
        denom = cpx( 2*coef.A,  0 );
    ComplexFraction f = ComplexFraction(numer, denom);
    return f.reduce();
}

std::vector< ComplexFraction > sequence( std::queue< coefficient > coef ) {
    std::vector< ComplexFraction > vec;
    while ( !vec.empty() ) { vec.pop_back(); }
    while ( !coef.empty() ) {
        ComplexFraction f = solution( coef.front() );
        /*
        bool flag = true;
        std::vector< ComplexFraction >::iterator itr=vec.begin();
        while (itr != vec.end()) {
            if (*itr == f) flag = false;
            ++itr;
        }
        // if (flag) vec.push_back( f );
        */
        if ( is_in_F( f ) ) vec.push_back( f );
        coef.pop();
    }
    return vec;
}

long class_number( long D ) {
    long res = sequence( get_coefficients( D ) ).size();
    return res;
}

/*
int main() {
    long D;
    std::cin >> D;
    std::cout << " class number of " << D
              << " is : " << class_number( D ) << std::endl;
    return 0;
}
*/
