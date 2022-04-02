#ifndef SUBJECT_H_
#define SUBJECT_H_
#include <vector>
class Observer;
class Subject {
    std::vector<Observer*> obs;
public:
    void notifyObservers();
    void attach(Observer*);
    void detach(Observer*);
    virtual ~Subject() = 0;
};
#endif