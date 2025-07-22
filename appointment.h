#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <QString>

class Appointment
{
public:
    Appointment();

    QString getStatusText();

    unsigned int id;
    QString datetime;
    QString reason;
    int status;
    int fk_patient;
};

#endif // APPOINTMENT_H
