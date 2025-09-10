#include "appointmentmodel.h"

QVector<AppointmentObserver*> AppointmentModel::AppointmentObservers;

AppointmentModel::AppointmentModel() {}

Appointment AppointmentModel::getAppointmentFromId(int id)
{
    return appointmentDao.getAppointmentFromId(id);
}

bool AppointmentModel::insertAppointment(const Appointment &app)
{
    bool result = appointmentDao.insertAppointment(app);

    AppointmentModel::UpdateObservers();

    return result;
}

QList<Appointment> AppointmentModel::getAppointmentsFromDateSorted(QString date)
{
    return appointmentDao.getAppointmentsFromDateSorted(date);
}

void AppointmentModel::updateAppointment(const Appointment &newAppointment)
{
    appointmentDao.updateAppointment(newAppointment);

    AppointmentModel::UpdateObservers();
}

void AppointmentModel::RegisterObserver(AppointmentObserver* newObserver)
{
    AppointmentModel::AppointmentObservers.append(newObserver);
}

void AppointmentModel::UpdateObservers()
{
    for(int i = 0; i < AppointmentModel::AppointmentObservers.size(); ++i)
    {
        AppointmentModel::AppointmentObservers[i]->UpdateAppointments();
    }
}

void AppointmentModel::UnregisterObserver(AppointmentObserver* observer)
{
    AppointmentModel::AppointmentObservers.removeOne(observer);
}
