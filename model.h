#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QSqlDatabase>
#include "patientdao.h"
#include "appointmentdao.h"
#include "placedao.h"
#include "statusdao.h"
#include <QCryptographicHash>
#include "report.h"
#include "reportdao.h"
#include "attachment.h"
#include "attachmentdao.h"
#include "credentialdao.h"

#include <QVector>
#include <QWidget>
#include "observer.h"

enum class ObserverType
{
    Appointments,
    Reports
};

class Model
{
public:
    Model();

    // OBSERVERS
    static void RegisterObserver(Observer* newObserver, ObserverType type);
    static void UnregisterObserver(Observer* observer, ObserverType type);
    static QVector<Observer*> AppointmentObservers;
    static QVector<Observer*> ReportObservers;

    // Authentication
    bool Authenticate(const QString& hashValue);
    void SetPassword(const QString& newPassword);

    // Manage patients
    QList<Patient> getAllPatientsSortedBySurname();
    bool insertPatient(const Patient& patient);
    Patient getPatientFromId(unsigned int id);
    Patient getPatientFromCf(const QString& cf);
    QList<Patient> getAllPatients();
    bool updatePatient(const Patient& newPatientData);

    // Manage appointments
    Appointment getAppointmentFromId(int id);
    bool insertAppointment(const Appointment& app);
    QList<Appointment> getAppointmentsFromDateSorted(QString date);
    void updateAppointment(const Appointment& newAppointment);

    // Manage statuses
    QString getStatusNameFromId(int id);
    QList<Status> getAllStatuses();

    // Manage places
    QList<Place> getAllPlaces();
    int getPlaceIdFromBelfiore(const QString& belfiore);

    // Manage reports
    int insertReport(const Report& report);
    QList<Report> getReportsOfPatient(int patientId);
    Report getReportFromId(int id);
    void deleteReport(int id);
    void updateReport(const Report& newReport);

    // Manage attachments
    bool insertAttachment(const Attachment& attachment);
    QList<Attachment> getAttachmentsOfReport(const Report &report);
    void deleteAttachment(const Attachment& attachment);

    // EMAIL SERVICE
    int sendReminder(const Patient& patient, const Appointment& appointment);

private:
    QSqlDatabase db;

    PatientDAO patientDao;
    AppointmentDAO appointmentDao;
    PlaceDAO placeDao;
    StatusDAO statusDao;
    ReportDAO reportDao;
    AttachmentDAO attachmentDao;
    CredentialDAO credentialDao;

    QCryptographicHash::Algorithm hashingFunction;

    static void UpdateObservers(const ObserverType observerType);
};

#endif // MODEL_H
