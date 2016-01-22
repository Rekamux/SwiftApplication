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
    return o << "{ " << r.n << " " << r.Fn << " " << r.state << " }";
}

bool is_prime( Type Fn )
{
    Type sr = std::sqrt( Fn );

    for( Type i = 2; i <= sr; i++ )
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
static IndexType eratosthenes_size = 0;

static void init_eratosthenes( IndexType n_max )
{
    IndexType size = n_max + 1;
    bool *new_e = nullptr;
    IndexType element_size;

    if( size <= eratosthenes_size )
    {
        return;
    }

    // Not released on purpose:  several executions of buzzfizz
    // in the same process will benefit from it.
    new_e = new bool[size];
    if( !new_e )
    {
        return;
    }

    element_size = sizeof( new_e[0] );

    if( eratosthenes )
    {
        memcpy( new_e, eratosthenes, eratosthenes_size * element_size );
        bzero( new_e + eratosthenes_size,
            (size - eratosthenes_size) * element_size );
        delete eratosthenes;
    }
    else
    {
        bzero( new_e, size * element_size );

        if( n_max >= 1 )
        {
            new_e[0] = new_e[1] = true;
        }
    }
    eratosthenes = new_e;
    eratosthenes_size = size;
}

// Slightly better optimized:  use the divisability property of Fibonacci
// to fasten the search
static bool is_Fn_prime( IndexType n_max, IndexType n, Type Fn )
{
    bool n_prime, Fn_prime = true;

    // Fn can get big, but not n.
    // Use Eratosthenes on n to fasten the process.
    if( eratosthenes && n < eratosthenes_size )
    {
        n_prime = !eratosthenes[n];

        if( n_prime )
        {
            for( IndexType i = n + n; i < eratosthenes_size; i += n )
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
    static constexpr Type mask = ((Type)1) << (TYPE_BITS - 1);

    // It will overflow if the MSBs of both are 1
    // or if one's MSB is 1 and the sum of the rest will set the MSB
    bool a_danger = a & mask;
    bool b_danger = b & mask;
    Type a_less_msb = a & ~mask;
    Type b_less_msb = b & ~mask;
    bool sum_danger = (a_less_msb + b_less_msb) & mask;

    return (!a_danger && !b_danger) ||
        ((a_danger || b_danger) && !sum_danger);
}

int buzzfizz( IndexType n_max, ResultHandler handler, void *ptr )
{
    Type Fn_prev = 0;
    Type Fn = 0;

    init_eratosthenes( n_max );

    for( IndexType n = 0; n <= n_max; n++ )
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

