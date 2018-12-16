#include "space.cpp"

typedef std::pair< long, long > longpair;


void print_fraction( long D ) {
    std::queue< coefficient > coef = get_coefficients( D );
    std::vector< ComplexFraction > frac = sequence( coef );
    for (int idx=0; idx<frac.size(); ++idx) {
        frac[idx].print();
    }
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

void solve( long D ) {
    std::queue< longpair > que;
    for (long num=D; num<0; ++num) {
        if ( (-num)%4 == 0 || (-num)%4 == 3 ) {
            que.push( std::make_pair(num, class_number( num ) ) );
        }
    }
    class_number_table( que );
}

int main() {
    long disc;
    std::cout << "THIS PROGRAM COMPUTES REPORT (9), \n"
              << "INPUT:\n"
              << "-----\n"
              << "  - LOWER BOUND OF DISCRIMINANT\n"
              << "OUTPUT:\n"
              << "------\n"
              << "  - MODE 1 : CLASS NUMBER OF DISCRIMINANT\n"
              << "  - MODE 2 : OUTPUT QUADRATIC IRATIONAL NUMBERS IN F\n"
              << "             CORRESPOND TO DISCRIMINANT D.\n";

    std::cout << "ENTER A LOWER BOUND OF DISCRIMINANT: \n";
    std::cin >> disc;

    solve( disc );
    print_fraction( -15 );

    return 0;
}
