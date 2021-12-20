/*
 * TimerSettingsInterface.h
 *
 *  Created on: 20.12.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_TIMERSETTINGSINTERFACE_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGSINTERFACE_H_

class TimerSettingsInterface {

public:
    // Empty virtual destructor for proper cleanup
    virtual ~TimerSettingsInterface() {}

    virtual int32_t getPT(const char* key) const = 0;
    virtual void setPT(const char* key, int32_t PT) = 0;
};



#endif /* COMPONENTS_PLCLIB_TIMERSETTINGSINTERFACE_H_ */
