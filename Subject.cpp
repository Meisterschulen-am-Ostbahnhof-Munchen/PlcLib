#include "Subject.h"
#include "Observer.h"

void Subject::attach (Observer* o) {
    _observers->Append(o);
    o->update(this); // at Attatching do a Update Directly !
}

void Subject::detach (Observer* o) {
    _observers->Remove(o);
}

void Subject::notify () {
    ListIterator<Observer*> i(_observers);

    for (i.First(); not i.IsDone(); i.Next()) {
        i.CurrentItem()->update(this);
    }
}

Subject::Subject() {
    _observers = new List<Observer*>();
}

