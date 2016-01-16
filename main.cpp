#include <iostream>
#include "buzzfizz.h"

using namespace std;
using namespace fb;

#define DECIMAL_BASE 10
#define ERR_OUT cerr

int usage( char *name )
{
    ERR_OUT << "Usage:  " << name << " last_index" << endl;
    return -1;
}

int main( int argc, char *argv[] )
{
    unsigned n = 0;

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

    return 0;
}

