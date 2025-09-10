#ifndef APPOINTMENTOBSERVER_H
#define APPOINTMENTOBSERVER_H

#include <QVector>

class AppointmentObserver
{
public:
    AppointmentObserver();

    virtual void UpdateAppointments() = 0;
};

#endif // APPOINTMENTOBSERVER_H
