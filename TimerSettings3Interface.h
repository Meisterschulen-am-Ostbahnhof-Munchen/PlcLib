/*
 * TimerSettings3Interface.h
 *
 *  Created on: 20.12.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_TIMERSETTINGS3INTERFACE_H_
#define COMPONENTS_PLCLIB_TIMERSETTINGS3INTERFACE_H_

class TimerSettings3Interface {

public:
    // Empty virtual destructor for proper cleanup
    virtual ~TimerSettings3Interface() {}

    virtual int32_t getPT_up(const char* key) const = 0;
    virtual int32_t getPT_down(const char* key) const = 0;
    virtual int32_t getPT_float(const char* key) const = 0;
    virtual void setPT_up(const char* key, int32_t PT_up) = 0;
    virtual void setPT_down(const char* key, int32_t PT_down) = 0;
    virtual void setPT_float(const char* key, int32_t PT_float) = 0;
};



#endif /* COMPONENTS_PLCLIB_TIMERSETTINGS3INTERFACE_H_ */
