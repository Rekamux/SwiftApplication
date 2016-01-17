#include <iostream>
#include <cmath>

#include "buzzfizz.h"

using namespace std;

namespace bf
{

ostream &operator<<( ostream &o, ResultState state )
{
    switch( state )
    {
    case ResultState::Buzz3 : return o << "Buzz3";
    case ResultState::Fizz5 : return o << "Fizz5";
    case ResultState::Buzz3Fizz5 : return o << "Buzz3Fizz5";
    case ResultState::BuzzFizzPrime : return o << "BuzzFizzPrime";
    case ResultState::Buzz3BuzzFizzPrime : return o << "Buzz3BuzzFizzPrime";
    case ResultState::Fizz5BuzzFizzPrime : return o << "Fizz5BuzzFizzPrime";
    case ResultState::Normal : return o << "Normal";
    }

    return o << "Unknown";
}

ostream &operator<<( ostream &o, Result r )
{
    return o << "{ " << r.n << " " << r.Fn << " " << r.state << "}";
}

// Basic prime test.  Slow but failure-proof.
static bool is_prime( Type Fn )
{
    Type sr = std::sqrt( Fn );

    for( Type i = 2; i < sr; i++ )
    {
        if( Fn % i == 0 )
        {
            return false;
        }
    }

    return true;
}

// Index is false iff prime or not discovered yet
static bool *eratosthenes = nullptr;

static void init_eratosthenes( IndexType n_max )
{
    IndexType size = n_max + 1;

    eratosthenes = new bool[size];
    if( !eratosthenes )
    {
        cerr << "Cannot allocate eratosthenes, expect slowness." << endl;
        return;
    }

    bzero( eratosthenes, size );

    if( n_max >= 1 )
    {
        eratosthenes[0] = eratosthenes[1] = true;
    }
}

// Slightly better optimized:  use the divisability property of Fibonacci
// to fasten the search
static bool is_Fn_prime( IndexType n_max, IndexType n, Type Fn )
{
    bool n_prime, Fn_prime = true;

    if( eratosthenes )
    {
        n_prime = !eratosthenes[n];

        if( n_prime )
        {
            for( IndexType i = n + n; i <= n_max; i += n )
            {
                eratosthenes[i] = true;
            }
        }
    }
    else
    {
        n_prime = is_prime( n );
    }

    // gcd( Fm, Fn ) = Fgcd( m, n )
    // i.e. if Fij there is a k such as Fij = kFi
    // i.e. if n isn't prime, Fn isn't prime
    if( !n_prime )
    {
        Fn_prime = false;
    }

    if( Fn_prime )
    {
        Fn_prime = is_prime( Fn );
    }

    return Fn_prime;
}

static ResultState get_state( IndexType n_max, IndexType n, Type Fn )
{
    bool div_3;
    bool div_5;

    if( Fn < 2 )
    {
        return ResultState::Normal;
    }

    if( Fn == 3 )
    {
        return ResultState::Buzz3BuzzFizzPrime;
    }

    if( Fn == 5 )
    {
        return ResultState::Fizz5BuzzFizzPrime;
    }

    div_3 = Fn % 3 == 0;
    div_5 = Fn % 5 == 0;

    if( div_3 )
    {
        if( div_5 )
        {
            return ResultState::Buzz3Fizz5;
        }
        return ResultState::Buzz3;
    }

    if( div_5 )
    {
        return ResultState::Fizz5;
    }

    if( is_Fn_prime( n_max, n, Fn ) )
    {
        return ResultState::BuzzFizzPrime;
    }

    return ResultState::Normal;
}

static bool addition_safe( Type a, Type b )
{
    // It will overflow iff the MSB of both is 1
    bool a_danger = a & (((Type)1) << (TYPE_BITS - 1));
    bool b_danger = b & (((Type)1) << (TYPE_BITS - 1));

    return !a_danger || !b_danger;
}

int buzzfizz( IndexType n_max, ResultHandler handler, void *ptr )
{
    Type Fn_prev = 0;
    Type Fn = 0;

    if( !eratosthenes )
    {
        init_eratosthenes( n_max );
    }

    for( IndexType n = 0; n < n_max; n++ )
    {
        if( n == 1 )
        {
            Fn = 1;
        }
        else
        {
            Type tmp = Fn_prev;
            Fn_prev = Fn;

            if( !addition_safe( Fn_prev, tmp ) )
            {
                cerr << "Overflow." << endl;
                return -1;
            }

            Fn += tmp;
        }
        Result res( n, Fn, get_state( n_max, n, Fn ) );

        if( handler )
        {
            int err = handler( ptr, res );

            if( err )
            {
                return err;
            }
        }
    }

    return 0;
}

} // namespace bf

