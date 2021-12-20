#include <stdint.h>
#include "TimerSettings.h"

TimerSettings::TimerSettings(TimerSettingsInterface* s)
	: _forward(s)
{

}

int32_t TimerSettings::getPT(const char* key) const {
    return (_forward->getPT(key));
}

void TimerSettings::setPT(const char* key, int32_t PT) {
	_forward->setPT(key, PT);
    notify();
}


