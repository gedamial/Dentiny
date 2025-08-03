#ifndef PATIENTDAO_H
#define PATIENTDAO_H
#include "patient.h"
#include <QString>

class PatientDAO
{
public:
    PatientDAO();

    bool insertPatient(const Patient& patient);
    Patient getPatientFromId(unsigned int id);
    Patient getPatientFromCf(const QString& cf);
    QList<Patient> getAllPatients();
    QList<Patient> getAllPatientsSortedBySurname();
};

#endif // PATIENTDAO_H
