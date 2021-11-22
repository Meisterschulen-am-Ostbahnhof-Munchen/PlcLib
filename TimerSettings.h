#ifndef COMPONENTS_PLCLIB_TIMERSETTINGS_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGS_H_

#include "Subject.h"

class TimerSettings : public Subject{
public:
	// Empty virtual destructor for proper cleanup
	virtual ~TimerSettings() {}

	TimerSettings();

	int32_t getPT() const;
	void setPT(int32_t PT);


private:
    int32_t PT;
};

#endif /* COMPONENTS_PLCLIB_TIMERSETTINGS_H_ */
