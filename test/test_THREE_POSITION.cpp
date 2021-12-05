/* test_PlcLib.c: Implementation of a testable component.


*/


#include "unity.h"
#include "Automation_THREE_POSITION.h"
#include "AutomationTimer_THREE_POSITION.h"

TEST_CASE("Test THREE_POSITION_TOF", "[PlcLib]")
{
	THREE_POSITION_SWITCH SWITCH;
	THREE_POSITION_TOF    TIMER;
	THREE_POSITION_VALVE  VALVE;
	TIMER.PT = 3000;


}



