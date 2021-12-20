#include <stdint.h>
#include "TimerSettings.h"


int32_t TimerSettings::getPT(const char* key) const {
    return (_forward->getPT(key));
}

void TimerSettings::setPT(const char* key, int32_t PT) {
	_forward->setPT(key, PT);
    notify();
}

TimerSettingsInterface* TimerSettings::getForward() {
	return (_forward);
}

TimerSettings* TimerSettings::getInstance() {
    if (instance == nullptr)
    {
        instance = new TimerSettings();
    }

    return (instance);
}

void TimerSettings::setForward(TimerSettingsInterface *forward) {
	TimerSettings::_forward = forward;
}


TimerSettingsInterface* TimerSettings::_forward = nullptr;
TimerSettings* TimerSettings::instance = nullptr;
