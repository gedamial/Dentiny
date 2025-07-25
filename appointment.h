#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <QString>

enum class AppointmentStatus
{
    Created = 0,
    Completed = 1,
    Canceled = 2
};

class Appointment
{
public:
    Appointment();

    unsigned int id;
    QString datetime;
    QString reason;
    int fk_status;
    int fk_patient;
};

#endif // APPOINTMENT_H
