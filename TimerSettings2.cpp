#include <stdint.h>
#include "TimerSettings2.h"

TimerSettings2::TimerSettings2() {
    _PT_up = 1000;
    _PT_down = 1000;
}


int32_t TimerSettings2::getPT_up(const char* key) const {
    return (_PT_up);
}

int32_t TimerSettings2::getPT_down(const char* key) const {
    return (_PT_down);
}

void TimerSettings2::setPT_up(const char* key, int32_t PT_up) {
    this->_PT_up = PT_up;
    notify();
}

void TimerSettings2::setPT_down(const char* key, int32_t PT_down) {
    this->_PT_down = PT_down;
    notify();
}
