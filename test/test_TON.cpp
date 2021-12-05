/* test_TON.cpp: Implementation of a testable component.


*/


#include "unity.h"
#include "StandardLib.h"

TEST_CASE("Test TON", "[PlcLib]")
{
    TON TON1;
    TON1.PT = 1000;
    TON1(true);
    TON1(false);

}



