#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    Observer();

    virtual void UpdateAppointments();
    virtual void UpdateReports();
};

#endif // OBSERVER_H
