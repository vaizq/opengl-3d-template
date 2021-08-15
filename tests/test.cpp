#include "catch_amalgamated.hpp"


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? 1: Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {

    REQUIRE( Factorial(0) == 1);

    constexpr int MAX = 10;

    SECTION( "Simple factorials" )
    {
        REQUIRE( Factorial(3) == 6 );
    }
}
