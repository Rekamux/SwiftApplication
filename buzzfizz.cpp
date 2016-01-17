#include <iostream>

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

int buzzfizz( int n, ResultHandler handler, void *ptr )
{
    Type Fn_prev = 0;
    Type Fn = 0;

    for( int i = 0; i < n; i++ )
    {
        if( i == 1 )
        {
            Fn = 1;
        }
        else
        {
            Type tmp = Fn_prev;
            Fn_prev = Fn;
            Fn += tmp;
        }
        Result res( i, Fn, ResultState::Normal );

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

