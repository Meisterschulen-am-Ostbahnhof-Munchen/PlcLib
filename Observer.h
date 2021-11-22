#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

//abstract class
class Observer {
public:
	// Empty virtual destructor for proper cleanup
	virtual ~Observer() {}
    virtual void Update(Subject* theChangedSubject) = 0;
};

#endif /* OBSERVER_H */
