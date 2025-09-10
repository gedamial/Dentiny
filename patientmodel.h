#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H
#include "patientdao.h"
#include "patient.h"

#include <QList>
#include <QString>

class PatientModel
{
public:
    PatientModel();

    QList<Patient> getAllPatientsSortedBySurname();
    bool insertPatient(const Patient& patient);
    Patient getPatientFromId(unsigned int id);
    Patient getPatientFromCf(const QString& cf);
    QList<Patient> getAllPatients();
    bool updatePatient(const Patient& newPatientData);

private:
     PatientDAO patientDao;
};

#endif // PATIENTMODEL_H
