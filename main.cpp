#include <iostream>

#include "buzzfizz.h"

using namespace std;
using namespace bf;

#define DECIMAL_BASE 10
#define ERR_OUT cerr

int usage( char *name )
{
    ERR_OUT << "Usage:  " << name << " last_index" << endl;
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

int main( int argc, char *argv[] )
{
    unsigned n = 0;
    int err;

    if( argc != 2 )
    {
        return usage( argv[0] );
    }

    n = strtol( argv[1], nullptr, 10 );
    if( errno == ERANGE )
    {
        ERR_OUT << "Out of range index" << endl;
        return usage( argv[0] );
    }

    err = buzzfizz( n, print_result, nullptr );
    if( err )
    {
        ERR_OUT << "Failure." << endl;
        return err;
    }

    return 0;
}

