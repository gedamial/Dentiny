#ifndef APPOINTMENTDAO_H
#define APPOINTMENTDAO_H
#include <QList>
#include "appointment.h"

class AppointmentDAO
{
public:
    AppointmentDAO();

    bool insertAppointment(const Appointment& app);
    QList<Appointment> getAppointmentsFromDateSorted(QString date);
};

#endif // APPOINTMENTDAO_H
