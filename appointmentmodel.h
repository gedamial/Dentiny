#ifndef APPOINTMENTMODEL_H
#define APPOINTMENTMODEL_H
#include "appointmentdao.h"
#include "appointmentobserver.h"
#include <QList>
#include <QString>

class AppointmentModel
{
public:
    AppointmentModel();

    Appointment getAppointmentFromId(int id);
    bool insertAppointment(const Appointment& app);
    QList<Appointment> getAppointmentsFromDateSorted(QString date);
    void updateAppointment(const Appointment& newAppointment);

    void RegisterObserver(AppointmentObserver* newObserver);
    void UpdateObservers();
    void UnregisterObserver(AppointmentObserver* observer);

private:
    AppointmentDAO appointmentDao;
    static QVector<AppointmentObserver*> AppointmentObservers;
};

#endif // APPOINTMENTMODEL_H
