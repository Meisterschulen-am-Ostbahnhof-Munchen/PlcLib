/* test_FOUR_POSITION.cpp: Implementation of a testable component.


*/


#include "unity.h"
#include "Automation_FOUR_POSITION.h"
#include "AutomationTimer_FOUR_POSITION.h"

TEST_CASE("Test FOUR_POSITION_TOF", "[PlcLib]")
{
    FOUR_POSITION_SWITCH SWITCH;
    FOUR_POSITION_TOF    TIMER;
    VALVE_WITH_FLOAT  VALVE;
    TIMER.PT = 3000;
    //TODO implement the Rest of the Test.


}



