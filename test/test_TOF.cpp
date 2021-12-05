/* test_TON.cpp: Implementation of a testable component.


*/


#include "unity.h"
#include "StandardLib.h"

TEST_CASE("Test TOF", "[PlcLib]")
{
    TOF TOF1;
    TOF1.PT = 1000;
    TOF1(true);
    TOF1(false);
    //TODO implement the Rest of the Test.


}



