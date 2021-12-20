#include <stdint.h>
#include "TimerSettings3.h"




int32_t TimerSettings3::getPT_up(const char* key) const {
    return (_forward->getPT_up(key));
}

int32_t TimerSettings3::getPT_down(const char* key) const {
    return (_forward->getPT_down(key));
}

int32_t TimerSettings3::getPT_float(const char* key) const {
    return (_forward->getPT_float(key));
}

void TimerSettings3::setPT_up(const char* key, int32_t PT_up) {
	_forward->setPT_up(key, PT_up);
    notify();
}

void TimerSettings3::setPT_down(const char* key, int32_t PT_down) {
	_forward->setPT_down(key, PT_down);
    notify();
}

void TimerSettings3::setPT_float(const char* key, int32_t PT_float) {
	_forward->setPT_float(key, PT_float);
    notify();
}


TimerSettings3Interface* TimerSettings3::getForward() {
	return (_forward);
}

TimerSettings3* TimerSettings3::getInstance() {
    if (instance == nullptr)
    {
        instance = new TimerSettings3();
    }

    return (instance);
}

void TimerSettings3::setForward(TimerSettings3Interface *forward) {
	TimerSettings3::_forward = forward;
}


TimerSettings3Interface* TimerSettings3::_forward = nullptr;
TimerSettings3* TimerSettings3::instance = nullptr;
