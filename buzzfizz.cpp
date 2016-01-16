#include "buzzfizz.h"

using namespace fb;

const char *getResultStateCString( ResultState state )
{
    switch( state )
    {
    case Buzz3 : return "Buzz3";
    case Fizz5 : return "Fizz5";
    case Buzz3Fizz5 : return "Buzz3Fizz5";
    case BuzzFizzPrime : return "BuzzFizzPrime";
    case Normal : return "Normal";
    }

    return "Unknown";
}

