#include <cmath>

#include <iostream>
#include <iomanip>
#include <map>
#include <queue>

typedef std::pair< long, long > longpair;
typedef struct _coef {
    long A, B, C;
} coef;

long gcd( long a, long b ) {
    if (b == 0) return a;
    a %= b;
    return gcd( b, a );
}

std::map< long, long > prime_factor( long n ) {
    std::map< long, long > res;
    for (int i=2; i*i<=n; ++i) {
        while ( n%i == 0 ) {
            ++res[ i ];
            n /= i;
        }
    }
    if ( n!= 1 ) res[ n ] = 1;
    return res;
}

// ***********************************************************************
// class QuadraticSolution
// ***********************************************************************

class QuadraticSolution {
private:    // Aw^2 + Bw + C;
    long numReal, numRoot;
    long denReal;
public:
    QuadraticSolution();
    QuadraticSolution( long a, long b, long c );
    QuadraticSolution( coef x );
    ~QuadraticSolution();
    bool operator==( const QuadraticSolution &rhs );
    bool operator!=( const QuadraticSolution &rhs );

    double real();
    double imag();
    double norm();

    std::pair< long, long > square_factorize();

    // QuadraticSolution rationarize();
    QuadraticSolution reduce();
    // QuadraticSolution conjugate();

    void print();
};

QuadraticSolution::QuadraticSolution() {
    numReal = 1;
    numRoot = 0;
    denReal = 1;
}

QuadraticSolution::QuadraticSolution( long a, long b, long c ) {
    numReal = -b;
    numRoot = 4*a*c - b*b;
    denReal = 2*a;
}

QuadraticSolution::QuadraticSolution( coef x ) {
    numReal = -x.B;
    numRoot = 4*x.A*x.C - x.B*x.B;
    denReal = 2*x.A;
}

QuadraticSolution::~QuadraticSolution() { }

bool QuadraticSolution::operator==( const QuadraticSolution &rhs ) {
    return (this->numReal == rhs.numReal) &&
           (this->numRoot == rhs.numRoot) &&
           (this->denReal   == rhs.denReal );
}

bool QuadraticSolution::operator!=( const QuadraticSolution &rhs ) {
    return !(*this == rhs);
}

double QuadraticSolution::real() {
    return (double) this->numReal / this->denReal;
}

double QuadraticSolution::imag() {
    return sqrt( this->numRoot ) / this->denReal;
}

double QuadraticSolution::norm() {
    double n, d;
    n = (double) this->numReal * this->numReal + this->numRoot;
    d = (double) this->denReal*this->denReal;
    return sqrt( n / d );
}

std::pair< long, long > QuadraticSolution::square_factorize() {
    long n = this->numRoot;
    std::pair< long, long > res = std::make_pair( 1, 1 );
    std::map< long, long > mp = prime_factor( n );
    std::map< long, long >::iterator itr = mp.begin();
    while ( itr != mp.end() ) {
        if ( itr->second == 1 ) {
            res.second *= itr->first;
        } else {
            long cnt = itr->second;
            while ( cnt > 1 ) {
                res.first *= itr->first;
                cnt -= 2;
            }
        }
        ++itr;
    }
    return res;
}

QuadraticSolution QuadraticSolution::reduce() {
    long num;
    QuadraticSolution q;
    std::pair< long, long > sq = this->square_factorize();
    num = gcd( abs(this->numReal), gcd( abs(this->denReal), abs(sq.first) )  );
    if ( num != 1 ) {
        q.numReal = this->numReal / num;
        long tmp = sq.first / num;
        q.numRoot = tmp*tmp*sq.second;
        q.denReal = this->denReal / num;
    }
    return q;
}
/*
QuadraticSolution QuadraticSolution::rationarize() {
    QuadraticSolution q;
}
*/
void QuadraticSolution::print() {
    std::cout << std::setw( 5 ) << this->numReal << '+'
              << "sqrt("
              << std::setw( 5 ) << this->numRoot
              << ") i\n"
              << "--------------------\n"
              << std::setw( 9 ) << this->denReal << '\n';
}

bool fundamental_space( QuadraticSolution q ) {
    /*
    bool cond1, cond2, cond3;
    cond1 = -0.5 <= q.real() && q.real() < 0.5;
    cond2 = q.norm() >= 1;
    if ( 0 < q.real() && q.real() < 0.5 ) {
        std::cout << "debug\n";
        cond3 = q.norm() > 1;
    } else {
        cond3 = true;
    }
    // std::cout << "q.norm() = " << q.norm() << std::endl;
    return cond1 && cond2 && cond3;
    */
    bool cond1, cond2;
    cond1 = -0.5 <= q.real() && q.real() < 0.5;
    if ( 0 < q.real() && q.real() < 0.5 ) {
        cond2 = q.norm() > 1;
    } else {
        cond2 = q.norm() >= 1;
    }
    std::cout << "q.norm() = " << q.norm() << std::endl;
    return cond1 && cond2;
}

std::queue< coef > get_coefficients( long d ) {
    long a, b, c;
    std::queue< coef > que;
    while (!que.empty()) { que.pop(); }
    a = sqrt( (double) abs(d)/3 );
    while ( a > 0 ) {
        for ( b=a; b>-a; --b ) {
            double _c = (double) (b*b - d) / (4*a);
            /*
            std::cout <<   " a=" << a
                      << "\n b=" << b
                      << "\n_c=" << _c << std::endl;
            */
            if ( _c == (int) _c ) {
                c = (b*b - d) / (4*a);
                if ( gcd( a, gcd( abs(b), abs(c) ) ) == 1 ) {
                    coef tmp = {.A=a, .B=b, .C=c};
                    /*
                    std::cout <<   "a=" << a
                              << "\nb=" << b
                              << "\nc=" << c << std::endl;
                    */
                    que.push(tmp);
                }
            }
        }
        --a;
    }
    return que;
}

std::queue< QuadraticSolution > sequence( std::queue< coef > Xs ) {
    std::queue< QuadraticSolution > que;
    while ( !que.empty() ) { que.pop(); }
    while ( !Xs.empty() ) {
        QuadraticSolution q( Xs.front() );
        q.reduce();
        if ( fundamental_space( q ) ) {
            que.push( q );
        }
        Xs.pop();
    }
    return que;
}

long class_number( long d ) {
    return sequence( get_coefficients( d ) ).size();
}

void class_number_table( std::queue< longpair > que ) {
    std::cout << "DISCRI | CLASS \n"
              << "MINANT | NUMBER\n"
              << "---------------" << std::endl;
    while ( !que.empty() ) {
        longpair q = que.front();
        std::cout << std::setw( 6 ) << q.first
                  << " | "
                  << std::setw( 6 ) << q.second
                  << std::endl;
        que.pop();
    }
    std::cout << "---------------" << std::endl;

}

// std::queue< longpair > class_numbers( long D ) {
void class_numbers( long D ) {
    std::queue< longpair > que;
    for (long num=-3; num>=D; --num) {
        if ( (-num)%4 == 0 || (-num)%4 == 3 ) {
            que.push( std::make_pair( num, class_number(num) ) );
        }
    }
    class_number_table( que );
}

void solve() {
    long d = -47;
    long cnt = 0;
    std::queue< coef > que = get_coefficients( d );
    while (!que.empty()) {
        coef X = que.front();
        que.pop();
        QuadraticSolution q(X);
        q.reduce();
        if ( fundamental_space(q) ) {
            q.print();
            ++cnt;
        } else {
            std::cout << "OUTSIDE OF FUNDAMENTAL SPACE\n";
            q.print();
            std::cout << "q.real() : " << q.real() << '\n'
                      << "q.imag() : " << q.imag() << '\n'
                      << "q.norm() : " << q.norm() << '\n'
                      << "q.print()\n"; q.print();
        }
    }
    std::cout << "class number is " << cnt << std::endl;
}

void description() {
    std::cout << "PROGRAM DESCRIPTION:\n"
              << "===================\n"
              << "  * INPUT\n"
              << "    - A NEGATIVE INTEGER (VALUE OF DISCRIMINANT)\n"
              << "  * OUTPUT\n"
              << "    - CLASS NUMBER OF EACH D <- {-3, -4, -7, .., INPUT} \n";
}

int main() {
    long disc;
    description();
    std::cout << "ENTER A NEGATIVE INTEGER > ";
    while ( std::cin >> disc, disc > -1 ) {
        std::cout << "THIS IS NOT A NEGATIVE INTEGER,\n"
                  << "RE-ENTER A NEGATIVE INTEGER AGAIN. > ";
    }
    class_numbers( disc );
    return 0;
}
