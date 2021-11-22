#include <stdint.h>
#include "TimerSettings.h"

TimerSettings::TimerSettings() {
	_PT = 1000;
}


int32_t TimerSettings::getPT() const {
	return (_PT);
}

void TimerSettings::setPT(int32_t PT) {
	this->_PT = PT;
    Notify();
}
