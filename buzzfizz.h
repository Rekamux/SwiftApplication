#include <climits>

#define ARRAY_SIZE( array ) (sizeof(array) / sizeof(array[0]))

namespace bf
{

// Used types:  define the Fibonacci limit
typedef unsigned IndexType;
typedef unsigned long long Type;
static constexpr IndexType TYPE_BITS = sizeof( Type ) * CHAR_BIT;

// State each Fn can be in
enum class ResultState
{
    Buzz3,              // Divisible by 3 and not 5
    Fizz5,              // Divisible by 5 and not 3
    Buzz3Fizz5,         // Divisible by 3 and 5
    BuzzFizzPrime,      // Prime number and not 3 nor 5
    Buzz3BuzzFizzPrime, // 3
    Fizz5BuzzFizzPrime, // 5
    Normal,             // None of the above
};
std::ostream &operator<<( std::ostream &o, ResultState r );

// Wrapper for each result
struct Result
{
    IndexType n;
    Type Fn;
    ResultState state;

    Result( IndexType n, Type Fn, ResultState state ) :
        n( n ), Fn( Fn ), state( state ) {}
    Result() : n( 0 ), Fn( 0 ), state( ResultState::Normal ) {}
};
std::ostream &operator<<( std::ostream &o, Result r );

// Callback for each result
// Return 0 on success, -1 otherwise.
typedef int (*ResultHandler)( void *ptr, Result );

// Call the handler for each result until n.
// Return 0 on success, -1 otherwise.
int buzzfizz( IndexType n, ResultHandler handler, void *ptr );

// Basic prime test, O(sqrt(n)).
bool is_prime( Type Fn );

} // namespace bf

