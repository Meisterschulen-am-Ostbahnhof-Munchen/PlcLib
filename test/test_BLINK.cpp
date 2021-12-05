/* test_BLINK.cpp: Implementation of a testable component.


*/


#include "unity.h"
#include "StandardLib.h"
#include "UtilLib.h"

TEST_CASE("Test BLINK", "[PlcLib]")
{
    BLINK BLINK1;
    BLINK1.TIMEHIGH = 500;
    BLINK1.TIMELOW = 100;
    BLINK1(true);
    BLINK1(false);
    //TODO implement the Rest of the Test.


}



