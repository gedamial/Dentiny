#ifndef APPOINTMENTDAO_H
#define APPOINTMENTDAO_H
#include <QList>
#include "appointment.h"
#include <QSqlQuery>

class AppointmentDAO
{
public:
    AppointmentDAO();

    Appointment loadFromQueryRow(const QSqlQuery& query);
    Appointment getAppointmentFromId(int id);
    bool insertAppointment(const Appointment& app);
    QList<Appointment> getAppointmentsFromDateSorted(QString date);
    void updateAppointment(const Appointment& newAppointment);
};

#endif // APPOINTMENTDAO_H
