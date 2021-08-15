#include "catch_amalgamated.hpp"
#include "tool.h"


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? 1: Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    Tool tool;
    REQUIRE( tool.kertoma(1) == 1);

    constexpr int MAX = 10;

    SECTION( "Small factorials" )
    {
        for(int i = 1; i < MAX/2; i++)
            REQUIRE( tool.kertoma(i) == Factorial(i) );
    }
    SECTION( "Large factorials" )
    {
         for(int i = 1; i < MAX; i++)
            REQUIRE( tool.kertoma(i) == Factorial(i) );
    }
}
