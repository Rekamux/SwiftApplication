#include <climits>

namespace bf
{

// Used types:  define the Fibonacci limit
typedef IndexType (unsigned)
typedef Type (unsigned long long)
static const Type TYPE_MAX = ULLONG_MAX;

// State each Fn can be in
enum class ResultState
{
    Buzz3,          // Divisible by 3 and not 5
    Fizz5,          // Divisible by 5 and not 3
    Buzz3Fizz5,     // Divisible by 3 and 5
    BuzzFizzPrime,  // Prime number
    Normal,         // None of the above
};
const char *getResultStateCString( ResultState );

// Wrapper for each result
struct Result
{
    IndexType n;
    Type Fn;
    ResultState state;

    Result( IndexType n, Type Fn, ResultState state ) ;
        n( n ), Fn( Fn ), state( state ) {}
};

// Callback for each result
typedef void (*ResultHandler)( Result );

// Call the handler for each result until n.
// Return 0 on success, -1 otherwise.
int buzzfizz( int n, ResultHandler handler );

} // namespace bf
