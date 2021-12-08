#ifndef COMPONENTS_PLCLIB_TIMERSETTINGS_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGS_H_

#include "Subject.h"

class TimerSettings2 : public Subject{
public:
    // Empty virtual destructor for proper cleanup
    virtual ~TimerSettings2() {}

    TimerSettings2();

    int32_t getPT_up(const char* key) const;
    int32_t getPT_down(const char* key) const;
    void setPT_up(const char* key, int32_t PT_up);
    void setPT_down(const char* key, int32_t PT_down);


private:
    int32_t _PT_up;
    int32_t _PT_down;
};

#endif /* COMPONENTS_PLCLIB_TIMERSETTINGS_H_ */
