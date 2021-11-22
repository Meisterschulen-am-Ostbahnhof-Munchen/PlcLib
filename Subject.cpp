#include "Subject.h"
#include "Observer.h"

void Subject::Attach (Observer* o) {
    _observers->Append(o);
    o->Update(this); // at Attatching do a Update Directly !
}

void Subject::Detach (Observer* o) {
    _observers->Remove(o);
}

void Subject::Notify () {
    ListIterator<Observer*> i(_observers);

    for (i.First(); !i.IsDone(); i.Next()) {
        i.CurrentItem()->Update(this);
    }
}

Subject::Subject() {
	_observers = new List<Observer*>();
}

