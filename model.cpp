#include "model.h"
#include "dbmanager.h"

Model::Model()
{
    db = DBManager::getInstance().getDatabase();
    hashingFunction = QCryptographicHash::Sha256;
}

bool Model::Authenticate(const QString& plaintext)
{
    QSqlQuery query("SELECT password FROM Credential", db);
    query.exec();
    query.next();

    const QString truePassword = query.value("password").toString();
    const QByteArray hashedValue = QCryptographicHash::hash(plaintext.toUtf8(), QCryptographicHash::Sha256);

    if(hashedValue.toHex() == truePassword)
    {
        return true;
    }

    return false;
}

void Model::SetPassword(const QString &newPassword)
{
    const QString newPasswordHashed = QCryptographicHash::hash(newPassword.toUtf8(), hashingFunction).toHex();

    QSqlQuery query(db);
    query.prepare("UPDATE Credential SET password = :newPassword");
    query.bindValue(":newPassword", newPasswordHashed);
    query.exec();
}

QList<Patient> Model::getAllPatientsSortedBySurname()
{
    return patientDao.getAllPatientsSortedBySurname();
}

bool Model::insertPatient(const Patient &patient)
{
    return patientDao.insertPatient(patient);
}

Patient Model::getPatientFromId(unsigned int id)
{
    return patientDao.getPatientFromId(id);
}

Patient Model::getPatientFromCf(const QString &cf)
{
    return patientDao.getPatientFromCf(cf);
}

QList<Patient> Model::getAllPatients()
{
    return patientDao.getAllPatients();
}

Appointment Model::getAppointmentFromId(int id)
{
    return appointmentDao.getAppointmentFromId(id);
}

bool Model::insertAppointment(const Appointment &app)
{
    return appointmentDao.insertAppointment(app);
}

QList<Appointment> Model::getAppointmentsFromDateSorted(QString date)
{
    return appointmentDao.getAppointmentsFromDateSorted(date);
}

void Model::updateAppointmentWithId(unsigned int id, const Appointment &newAppointment)
{
    return appointmentDao.UpdateAppointmentWithId(id, newAppointment);
}

QString Model::getStatusNameFromId(int id)
{
    return statusDao.getStatusNameFromId(id);
}

QList<Status> Model::getAllStatuses()
{
    return statusDao.getAllStatuses();
}

QList<Place> Model::getAllPlaces()
{
    return placeDao.getAllPlaces();
}

int Model::getPlaceIdFromBelfiore(const QString &belfiore)
{
    return placeDao.getPlaceIdFromBelfiore(belfiore);
}
