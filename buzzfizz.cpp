#include "buzzfizz.h"

namespace bf
{

const char *getResultStateCString( ResultState state )
{
    switch( state )
    {
    case ResultState::Buzz3 : return "Buzz3";
    case ResultState::Fizz5 : return "Fizz5";
    case ResultState::Buzz3Fizz5 : return "Buzz3Fizz5";
    case ResultState::BuzzFizzPrime : return "BuzzFizzPrime";
    case ResultState::Buzz3BuzzFizzPrime : return "Buzz3BuzzFizzPrime";
    case ResultState::Fizz5BuzzFizzPrime : return "Fizz5BuzzFizzPrime";
    case ResultState::Normal : return "Normal";
    }

    return "Unknown";
}

int buzzfizz( int n, ResultHandler handler, void *ptr )
{
    for( int i = 0; i < n; i++ )
    {
        Result res( i, i, ResultState::Normal );
        handler( ptr, res );
    }

    return 0;
}

} // namespace bf

