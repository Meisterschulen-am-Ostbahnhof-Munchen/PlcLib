#ifndef COMPONENTS_PLCLIB_TIMERSETTINGS_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGS_H_

#include "Subject.h"
#include "TimerSettings2Interface.h"

class TimerSettings2 : public TimerSettings2Interface, public Subject{
public:
    // Empty virtual destructor for proper cleanup
    virtual ~TimerSettings2() {}

    int32_t getPT_up(const char* key) const;
    int32_t getPT_down(const char* key) const;
    void setPT_up(const char* key, int32_t PT_up);
    void setPT_down(const char* key, int32_t PT_down);


    static TimerSettings2* getInstance( );
	static TimerSettings2Interface* getForward();
	static void setForward(TimerSettings2Interface *forward);

	TimerSettings2(const TimerSettings2& a) = delete;
	TimerSettings2& operator=(const TimerSettings2& other) = delete;

private:
	TimerSettings2() = default;
    static TimerSettings2Interface* _forward;
    static TimerSettings2* instance;
};

#endif /* COMPONENTS_PLCLIB_TIMERSETTINGS_H_ */
