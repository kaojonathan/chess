#ifndef OBSERVER_H_
#define OBSERVER_H_
class Observer {
public:
    virtual ~Observer();
    virtual void notify() = 0;
};

#endif
