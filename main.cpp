#include <iostream>

#include "buzzfizz.h"

using namespace std;
using namespace bf;

#define DECIMAL_BASE 10

int usage( char *name )
{
    cerr << "Usage:  " << name << " last_index [-v]" << endl;
    return -1;
}

int print_result( void *ptr, Result res )
{
    switch( res.state )
    {
    case ResultState::Buzz3 :
        cout << "Buzz";
        break;
    case ResultState::Fizz5 :
        cout << "Fizz";
        break;
    case ResultState::Buzz3Fizz5 :
        cout << "Buzz Fizz";
        break;
    case ResultState::BuzzFizzPrime :
        cout << "BuzzFizz";
        break;
    case ResultState::Buzz3BuzzFizzPrime :
        cout << "Buzz BuzzFizz";
        break;
    case ResultState::Fizz5BuzzFizzPrime :
        cout << "Fizz BuzzFizz";
        break;
    case ResultState::Normal :
        cout << res.Fn;
        break;
    }

    cout << endl;

    return 0;
}

int print_verbose_result( void *ptr, Result res )
{
    cout << res << endl;
    return 0;
}

int main( int argc, char *argv[] )
{
    unsigned n = 0;
    int err;
    bool verbose = argc == 3;

    if( argc != 2 && !verbose )
    {
        return usage( argv[0] );
    }

    n = strtol( argv[1], nullptr, 10 );
    if( errno == ERANGE )
    {
        cerr << "Out of range index" << endl;
        return usage( argv[0] );
    }

    if( verbose )
    {
        err = buzzfizz( n, print_verbose_result, nullptr );
    }
    else
    {
        err = buzzfizz( n, print_result, nullptr );
    }
    if( err )
    {
        cerr << "Failure." << endl;
        return err;
    }

    return 0;
}

