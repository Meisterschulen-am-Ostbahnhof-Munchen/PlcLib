#include <stdint.h>
#include "TimerSettings2.h"




int32_t TimerSettings2::getPT_up(const char* key) const {
    return (_forward->getPT_up(key));
}

int32_t TimerSettings2::getPT_down(const char* key) const {
    return (_forward->getPT_down(key));
}

void TimerSettings2::setPT_up(const char* key, int32_t PT_up) {
	_forward->setPT_up(key, PT_up);
    notify();
}

void TimerSettings2::setPT_down(const char* key, int32_t PT_down) {
	_forward->setPT_down(key, PT_down);
    notify();
}

TimerSettings2Interface* TimerSettings2::getForward() {
	return (_forward);
}

TimerSettings2* TimerSettings2::getInstance() {
    if (instance == nullptr)
    {
        instance = new TimerSettings2();
    }

    return (instance);
}

TimerSettings2* TimerSettings2::getInstance(TimerSettings2Interface *forward) {
    if (instance == nullptr)
    {
    	TimerSettings2::setForward(forward);
        instance = new TimerSettings2();
    }

    return (instance);
}

void TimerSettings2::setForward(TimerSettings2Interface *forward) {
	TimerSettings2::_forward = forward;
}


TimerSettings2Interface* TimerSettings2::_forward = nullptr;
TimerSettings2* TimerSettings2::instance = nullptr;
