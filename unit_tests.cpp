#include <iostream>

#include "buzzfizz.h"

using namespace bf;
using namespace std;

static constexpr IndexType overflow_val = 94;

// Covers all the possible states
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

static constexpr int expected_size = ARRAY_SIZE( expected );

static ResultState get_state( Type Fn )
{
    bool div_3;
    bool div_5;

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

    if( is_prime( Fn ) )
    {
        return ResultState::BuzzFizzPrime;
    }

    return ResultState::Normal;
}

struct LastFibonacci
{
    Type pp;
    Type p;
};

int test_result( void *ptr, Result res )
{
    Result exp;
    LastFibonacci *last = (LastFibonacci *)ptr;
    int err = 0;

    if( res.n < expected_size )
    {
        exp = expected[res.n];
    }
    else if( !last )
    {
        cerr << "Null ptr passed." << endl;
        return -1;
    }
    else
    {
        Type Fn = last->pp + last->p;
        ResultState state = get_state( Fn );

        last->pp = last->p;
        last->p = Fn;

        exp = Result( res.n, Fn, state );
    }

    if( exp.Fn != res.Fn )
    {
        cerr << "Wrong Fn." << endl;
        err = -1;
    }

    if( exp.state != res.state )
    {
        cerr << "Wrong State." << endl;
        err = -1;
    }

    if( err )
    {
        cerr << "Expected: " << exp << endl
             << "Got:      " << res << endl
             << endl;
    }

    return err;
}

int main( int argc, char *argv[] )
{
    int err;
    LastFibonacci last;

    cout << "Testing the few firsts..." << endl;
    err = buzzfizz( expected_size - 1, test_result, nullptr );
    if( err )
    {
        cerr << "Unit tests failed." << endl;
        return err;
    }

    last.pp = expected[expected_size-2].Fn;
    last.p = expected[expected_size-1].Fn;

    cout << "Testing until overflow " << overflow_val << "..." << endl;
    err = buzzfizz( overflow_val - 1, test_result, &last );
    if( err )
    {
        cerr << "Unit tests failed." << endl;
        return err;
    }

    cout << "Testing overflow..." << endl;
    err = buzzfizz( overflow_val, nullptr, nullptr );
    if( !err )
    {
        cerr << "Failed to detect overflow." << endl;
        return -1;
    }

    cout << "Success!" << endl;

    return 0;
}

