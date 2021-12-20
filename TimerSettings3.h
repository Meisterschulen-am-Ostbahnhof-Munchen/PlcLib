#ifndef COMPONENTS_PLCLIB_TIMERSETTINGS_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGS_H_

#include "Subject.h"
#include "TimerSettings3Interface.h"

class TimerSettings3 : public TimerSettings3Interface, public Subject{
public:
    // Empty virtual destructor for proper cleanup
    virtual ~TimerSettings3() {}

    int32_t getPT_up(const char* key) const;
    int32_t getPT_down(const char* key) const;
    int32_t getPT_float(const char* key) const;
    void setPT_up(const char* key, int32_t PT_up);
    void setPT_down(const char* key, int32_t PT_down);
    void setPT_float(const char* key, int32_t PT_float);


    static TimerSettings3* getInstance( );
	static TimerSettings3Interface* getForward();
	static void setForward(TimerSettings3Interface *forward);

	TimerSettings3(const TimerSettings3& a) = delete;
	TimerSettings3& operator=(const TimerSettings3& other) = delete;

private:
	TimerSettings3() = default;
    static TimerSettings3Interface* _forward;
    static TimerSettings3* instance;
};

#endif /* COMPONENTS_PLCLIB_TIMERSETTINGS_H_ */
