#include <stdint.h>
#include "TimerSettings3.h"

TimerSettings3::TimerSettings3() {
    _PT_up = 1000;
    _PT_down = 1000;
    _PT_float = 1000;
}


int32_t TimerSettings3::getPT_up(const char* key) const {
    return (_PT_up);
}

int32_t TimerSettings3::getPT_down(const char* key) const {
    return (_PT_down);
}

int32_t TimerSettings3::getPT_float(const char* key) const {
    return (_PT_float);
}

void TimerSettings3::setPT_up(const char* key, int32_t PT_up) {
    this->_PT_up = PT_up;
    notify();
}

void TimerSettings3::setPT_down(const char* key, int32_t PT_down) {
    this->_PT_down = PT_down;
    notify();
}

void TimerSettings3::setPT_float(const char* key, int32_t PT_float) {
    this->_PT_float = PT_float;
    notify();
}
