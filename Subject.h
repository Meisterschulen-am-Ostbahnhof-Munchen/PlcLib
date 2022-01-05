#ifndef SUBJECT_H
#define SUBJECT_H

#include "ItemList.h"

class Observer;

class Subject {
public:
    // Empty virtual destructor for proper cleanup
    virtual ~Subject() {}

    virtual void attach(Observer*);
    virtual void detach(Observer*);
    virtual void notify();
    Subject();
    Subject(const Subject& a) = delete;
    Subject& operator=(const Subject& other) = delete;
private:
    List<Observer*> *_observers;
};

#endif /* SUBJECT_H */
