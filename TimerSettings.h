#ifndef COMPONENTS_PLCLIB_TIMERSETTINGS_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGS_H_

#include "Subject.h"
#include "TimerSettingsInterface.h"

class TimerSettings : public TimerSettingsInterface, public Subject{
public:
    // Empty virtual destructor for proper cleanup
    virtual ~TimerSettings() {}
    static TimerSettings* getInstance( );

    int32_t getPT(const char* key) const;
    void setPT(const char* key, int32_t PT);

	static TimerSettingsInterface* getForward();
	static void setForward(TimerSettingsInterface *forward);

private:
	TimerSettings() = default;
    static TimerSettingsInterface* _forward;
    static TimerSettings* instance;
};

#endif /* COMPONENTS_PLCLIB_TIMERSETTINGS_H_ */
