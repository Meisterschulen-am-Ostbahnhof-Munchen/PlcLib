#include <stdint.h>
#include "TimerSettings.h"

TimerSettings::TimerSettings() {
	PT = 1000;
}


int32_t TimerSettings::getPT() const {
	return PT;
}

void TimerSettings::setPT(int32_t PT) {
	this->PT = PT;
    Notify();
}
