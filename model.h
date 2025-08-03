#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QSqlDatabase>
#include "patientdao.h"
#include "appointmentdao.h"
#include "placedao.h"
#include "statusdao.h"
#include <QCryptographicHash>

class Model
{
public:
    Model();

    // Authentication
    bool Authenticate(const QString& hashValue);
    void SetPassword(const QString& newPassword);

    // Manage patients
    QList<Patient> getAllPatientsSortedBySurname();
    bool insertPatient(const Patient& patient);
    Patient getPatientFromId(unsigned int id);
    Patient getPatientFromCf(const QString& cf);
    QList<Patient> getAllPatients();

    // Manage appointments
    Appointment getAppointmentFromId(int id);
    bool insertAppointment(const Appointment& app);
    QList<Appointment> getAppointmentsFromDateSorted(QString date);
    void updateAppointmentWithId(unsigned int id, const Appointment& newAppointment);

    // Manage statuses
    QString getStatusNameFromId(int id);
    QList<Status> getAllStatuses();

    // Manage places
    QList<Place> getAllPlaces();
    int getPlaceIdFromBelfiore(const QString& belfiore);

private:
    QSqlDatabase db;

    PatientDAO patientDao;
    AppointmentDAO appointmentDao;
    PlaceDAO placeDao;
    StatusDAO statusDao;

    QCryptographicHash::Algorithm hashingFunction;
};

#endif // MODEL_H
