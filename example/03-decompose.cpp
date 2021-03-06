// C++11 - use assertions, observe reports with expression left and right side expanded.

#include "lest_decompose.hpp"

using namespace lest;

char a() { return 'a'; }
char b() { return 'b'; }

int  x() { return 3; }
int  y() { return 7; }

double pi() { return 3.14; }
double  e() { return 2.72; }

bool t() { return true; }
bool f() { return false; }

void * ptr() { return 0; }

class C {};

std::string std_hello( "hello" );
std::string std_world( "world" );

char const* hello( "hello" );
char const* world( "world" );

const lest::test specification[] =
{
    CASE( "character" )
    {
        EXPECT( a() < b() );
        EXPECT( b() < a() );
    },

    CASE( "integral" )
    {
        EXPECT(  x() != y() );
        EXPECT(  x() == y() );
    },

    CASE( "real" )
    {
        EXPECT(  pi() != e() );
        EXPECT(  pi() != pi() );
    },

    CASE( "mixed real, integral" )
    {
        EXPECT(  pi() != x() );
        EXPECT(  pi() == x() );
    },

    CASE( "mixed integral, real" )
    {
        EXPECT(  x() != pi() );
        EXPECT(  x() == pi() );
    },

    CASE( "boolean" )
    {
        EXPECT(  t() == t() );
        EXPECT(  t() == f() );
    },

    CASE( "pointer" )
    {
        EXPECT(  ptr() == nullptr );
        EXPECT(  ptr() != nullptr );
    },

    CASE( "class object pointer" )
    {
        C a; C b;
        EXPECT(  &a == &a );
        EXPECT(  &a == &b );
    },

    CASE( "std::string" )
    {
        EXPECT( std_world > std_hello );
        EXPECT( std_world < std_hello );
    },

    CASE( "C-string" )
    {
        EXPECT( world > std_hello );
        EXPECT( world < std_hello );
    },

    CASE( "single evaluation" )
    {
        int n = 0;
        EXPECT( 1 == ++n );
    },

    CASE( "duplicate evaluation" )
    {
        int n = 0;
        EXPECT( 2 == ++n );
    },
};

int main()
{
    return lest::run( specification );
}

// cl -nologo -Wall -EHsc -I../include/lest 03-decompose.cpp && 03-decompose
// g++ -Wall -Wextra -std=c++11 -I../include/lest -o 03-decompose.exe 03-decompose.cpp && 03-decompose

// 03-decompose.cpp:34: failed: character: b() < a() for 'b' < 'a'
// 03-decompose.cpp:40: failed: integral: x() == y() for 3 == 7
// 03-decompose.cpp:46: failed: real: pi() != pi() for 3.14 != 3.14
// 03-decompose.cpp:52: failed: mixed real, integral: pi() == x() for 3.14 == 3
// 03-decompose.cpp:58: failed: mixed integral, real: x() == pi() for 3 == 3.14
// 03-decompose.cpp:64: failed: boolean: t() == f() for true == false
// 03-decompose.cpp:70: failed: pointer: ptr() != nullptr for 0 != nullptr
// 03-decompose.cpp:77: failed: class object pointer: &a == &b for 0x28fdc7 == 0x28fdc6
// 03-decompose.cpp:83: failed: std::string: std_world < std_hello for "world" < "hello"
// 03-decompose.cpp:89: failed: C-string: world < std_hello for "world" < "hello"
// 03-decompose.cpp:101: failed: duplicate evaluation: 2 == ++n for 2 == 1
// 11 out of 12 tests failed.
