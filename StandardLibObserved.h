/*
 * StandardLibObserved.h
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_STANDARDLIBOBSERVED_H_
#define COMPONENTS_PLCLIB_STANDARDLIBOBSERVED_H_


#include "Observer.h"

class TimerSettings;
class Subject;


/**
 * \brief
    Timer on delay.
    Q is TRUE, PT milliseconds after IN had a rising edge.
 *
 * \param    IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return    Q is TRUE, PT milliseconds after IN had a rising edge.
 *
 */
class TON_O  : public Observer
{
public:
    TON_O(TimerSettings*, const char * const key);
    TON_O(const TON_O& a) = delete;
    TON_O& operator=(const TON_O& other) = delete;
    virtual ~TON_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    //VAR_OUTPUT
    bool Q = false;         /* is TRUE, PT milliseconds after IN had a rising edge */
    int32_t ET = 0;         /* elapsed time */
    //call
    bool operator()(bool IN);/* is TRUE, PT milliseconds after IN had a rising edge */
private:
    bool M = false;            /* internal variable */
    int32_t PT = 0;            /* internal variable */
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings* _subject;
    const char * const _key;
};


/**
 * \brief
    Timer of delay.
    Q is FALSE, PT milliseconds after IN had a falling edge.
 *
 * \param    IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return    Q is FALSE, PT seconds after IN had a falling edge
 *
 */
class TOF_O  : public Observer
{
public:
    TOF_O(TimerSettings*, const char * const key);
    TOF_O(const TOF_O& a) = delete;
    TOF_O& operator=(const TOF_O& other) = delete;
    virtual ~TOF_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    //VAR_OUTPUT
    bool Q = false;         /* Q is FALSE, PT milliseconds after IN had a falling edge */
    int32_t ET = 0;         /* elapsed time */
    //call
    bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
    bool M = false;            /* internal variable */
    int32_t PT = 0;            /* internal variable */
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings* _subject;
    const char * const _key;
};



/**
 * \brief
    Timer of delay.
    Q is FALSE, PT milliseconds after IN had a falling edge.


TOF_1 will extend a pulse on input in for PT seconds.
in addition the timer can be cleared asynchronously with rst.
TOF_1 is the same function as TOF from the standard LIB except the asynchronous reset input.

 *
 * \param    IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return    Q is FALSE, PT seconds after IN had a falling edge
 *
 */
class TOF_1_O  : public Observer
{
public:
    TOF_1_O(TimerSettings*, const char * const key);
    TOF_1_O(const TOF_1_O& a) = delete;
    TOF_1_O& operator=(const TOF_1_O& other) = delete;
    virtual ~TOF_1_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    bool RST = false;
    //VAR_OUTPUT
    bool Q = false;                    /* Q is FALSE, PT milliseconds after IN had a falling edge */
    int32_t ET = 0;         /* elapsed time */
    //call
    bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
    bool M = false;            /* internal variable */
    int32_t PT = 0;            /* internal variable */
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings* _subject;
    const char * const _key;
};



/**
 * \brief
    Timer of delay.
    Q is FALSE, PT milliseconds after IN had a Rising Edge !!!!!!.


TOF_1 will extend a pulse on input in for PT seconds.
in addition the timer can be cleared asynchronously with rst.
TOF_1 is the same function as TOF from the standard LIB except the asynchronous reset input and the Rising Edge Fact.

 *
 * \param    IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return    Q is FALSE, PT seconds after IN had a falling edge
 *
 */
class TOF_R_TRIG_O : public Observer
{
public:
    TOF_R_TRIG_O(TimerSettings*, const char * const key);
    TOF_R_TRIG_O(const TOF_R_TRIG_O& a) = delete;
    TOF_R_TRIG_O& operator=(const TOF_R_TRIG_O& other) = delete;
    virtual ~TOF_R_TRIG_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    bool RST = false;
    //VAR_OUTPUT
    bool Q = false;                    /* Q is FALSE, PT milliseconds after IN had a falling edge */
    int32_t ET = 0;         /* elapsed time */
    //call
    bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
    bool M = false;            /* internal variable */
    int32_t PT = 0;            /* internal variable */
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings* _subject;
    const char * const _key;
};


/**
 * \brief
    Timer Pulse.
    Q produces a High-Signal with the length of PT on every rising edge on IN.
 *
 * \param    IN Trigger for Start of the Signal
 * \param   PT The length of the High-Signal in ms
 * \return    Q is The pulse
 *
 */
class TP_O  : public Observer
{
public:
    TP_O(TimerSettings*, const char * const key);
    TP_O(const TP_O& a) = delete;
    TP_O& operator=(const TP_O& other) = delete;
    virtual ~TP_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    //VAR_OUTPUT
    bool Q = false;                    /* The pulse */
    int32_t ET = 0;         /* The current phase of the High-Signal  */
    //call
    bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
    bool M = false;            /* internal variable */
    int32_t PT = 0;            /* internal variable */
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings* _subject;
    const char * const _key;
};




#endif /* COMPONENTS_PLCLIB_STANDARDLIBOBSERVED_H_ */
