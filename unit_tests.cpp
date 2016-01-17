#include "buzzfizz.h"
#include "utils.h"
#include <iostream>

using namespace bf;
using namespace std;

void test_result( void *ptr, Result res )
{
    static const Result expected[] =
    {
        { 0, 0, ResultState::Normal },
        { 1, 1, ResultState::Normal },
        { 2, 1, ResultState::Normal },
        { 3, 2, ResultState::BuzzFizzPrime },
        { 4, 3, ResultState::Buzz3BuzzFizzPrime },
        { 5, 5, ResultState::Fizz5BuzzFizzPrime },
        { 6, 8, ResultState::Normal },
        { 7, 13, ResultState::BuzzFizzPrime },
        { 8, 21, ResultState::Buzz3 },
        { 9, 34, ResultState::Normal },
        { 10, 55, ResultState::Fizz5 },
        { 11, 89, ResultState::BuzzFizzPrime },
        { 12, 144, ResultState::Buzz3 },
        { 13, 233, ResultState::BuzzFizzPrime },
        { 14, 377, ResultState::Normal },
        { 15, 610, ResultState::Fizz5 },
        { 16, 987, ResultState::Buzz3 },
        { 17, 1597, ResultState::BuzzFizzPrime },
        { 18, 2584, ResultState::Normal },
        { 19, 4181, ResultState::Normal },
        { 20, 6765, ResultState::Buzz3Fizz5 },
    };
    static constexpr int size = ARRAY_SIZE( expected );

    if( res.n >= size ) return;
    cout << res.n << " " << res.Fn << " " <<
        getResultStateCString( res.state ) << endl;
}

int main( int argc, char *argv[] )
{
    return 0;
}

