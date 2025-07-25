#ifndef APPOINTMENTDAO_H
#define APPOINTMENTDAO_H
#include <QList>
#include "appointment.h"
#include <QSqlQuery>

class AppointmentDAO
{
public:
    AppointmentDAO();

    Appointment LoadFromQueryRow(const QSqlQuery& query);
    Appointment getAppointmentFromId(unsigned int id);
    bool insertAppointment(const Appointment& app);
    QList<Appointment> getAppointmentsFromDateSorted(QString date);
    void UpdateAppointmentWithId(unsigned int id, const Appointment& newAppointment);
};

#endif // APPOINTMENTDAO_H
