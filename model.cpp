#include "model.h"
#include "dbmanager.h"

Model::Model()
{
    db = DBManager::getInstance().getDatabase();
    hashingFunction = QCryptographicHash::Sha256;
}

QVector<Observer*> Model::AppointmentObservers;
QVector<Observer*> Model::ReportObservers;

void Model::RegisterObserver(Observer* newObserver, ObserverType type)
{
    if(type == ObserverType::Appointments)
    {
        Model::AppointmentObservers.append(newObserver);
    }

    else if(type == ObserverType::Reports)
    {
        Model::ReportObservers.append(newObserver);
    }
}

void Model::UnregisterObserver(Observer* observer, ObserverType type)
{
    if(type == ObserverType::Appointments)
    {
        Model::AppointmentObservers.removeOne(observer);
    }

    else if(type == ObserverType::Reports)
    {
        Model::ReportObservers.removeOne(observer);
    }
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

bool Model::updatePatient(const Patient &newPatientData)
{
    return patientDao.updatePatient(newPatientData);
}

Appointment Model::getAppointmentFromId(int id)
{
    return appointmentDao.getAppointmentFromId(id);
}

bool Model::insertAppointment(const Appointment &app)
{
    bool result = appointmentDao.insertAppointment(app);

    Model::UpdateObservers(ObserverType::Appointments);

    return result;
}

QList<Appointment> Model::getAppointmentsFromDateSorted(QString date)
{
    return appointmentDao.getAppointmentsFromDateSorted(date);
}

void Model::updateAppointment(const Appointment &newAppointment)
{
    appointmentDao.updateAppointment(newAppointment);

    Model::UpdateObservers(ObserverType::Appointments);
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

int Model::insertReport(const Report &report)
{
    int result = reportDao.insertReport(report);

    Model::UpdateObservers(ObserverType::Reports);

    return result;
}

QList<Report> Model::getReportsOfPatient(int patientId)
{
    return reportDao.getReportsOfPatient(patientId);
}

Report Model::getReportFromId(int id)
{
    return reportDao.getReportFromId(id);
}

void Model::deleteReport(int id)
{
    reportDao.deleteReport(id);

    Model::UpdateObservers(ObserverType::Reports);
}

void Model::updateReport(const Report &report)
{
    reportDao.updateReport(report);
    Model::UpdateObservers(ObserverType::Reports);
}

bool Model::insertAttachment(const Attachment &attachment)
{
    return attachmentDao.insertAttachment(attachment);
}

QList<Attachment> Model::getAttachmentsOfReport(const Report &report)
{
    return attachmentDao.getAttachmentsOfReport(report);
}

void Model::deleteAttachment(const Attachment &attachment)
{
    attachmentDao.deleteAttachment(attachment);
}

void Model::UpdateObservers(const ObserverType observerType)
{
    if(observerType == ObserverType::Appointments)
    {
        for(int i = 0; i < Model::AppointmentObservers.size(); ++i)
        {
            Model::AppointmentObservers[i]->UpdateAppointments();
        }
    }

    else if(observerType == ObserverType::Reports)
    {
        for(int i = 0; i < Model::ReportObservers.size(); ++i)
        {
            Model::ReportObservers[i]->UpdateReports();
        }
    }
}
