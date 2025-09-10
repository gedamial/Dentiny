#include "patientmodel.h"

PatientModel::PatientModel() {}

QList<Patient> PatientModel::getAllPatientsSortedBySurname()
{
    return patientDao.getAllPatientsSortedBySurname();
}

bool PatientModel::insertPatient(const Patient &patient)
{
    return patientDao.insertPatient(patient);
}

Patient PatientModel::getPatientFromId(unsigned int id)
{
    return patientDao.getPatientFromId(id);
}

Patient PatientModel::getPatientFromCf(const QString &cf)
{
    return patientDao.getPatientFromCf(cf);
}

QList<Patient> PatientModel::getAllPatients()
{
    return patientDao.getAllPatients();
}

bool PatientModel::updatePatient(const Patient &newPatientData)
{
    return patientDao.updatePatient(newPatientData);
}
