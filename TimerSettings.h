#ifndef COMPONENTS_PLCLIB_TIMERSETTINGS_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGS_H_

#include "Subject.h"
#include "TimerSettingsInterface.h"

class TimerSettings : public TimerSettingsInterface, public Subject{
public:
    // Empty virtual destructor for proper cleanup
    virtual ~TimerSettings() {}

    TimerSettings() = delete;
    TimerSettings(TimerSettingsInterface*);

    int32_t getPT(const char* key) const;
    void setPT(const char* key, int32_t PT);


private:
    TimerSettingsInterface* _forward;
};

#endif /* COMPONENTS_PLCLIB_TIMERSETTINGS_H_ */
