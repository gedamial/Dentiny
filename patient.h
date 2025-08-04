#ifndef PATIENT_H
#define PATIENT_H
#include <QString>

enum class PatientSex
{
    Male = 0,
    Female = 1
};

class Patient
{
public:
    Patient();

    unsigned int id;
    QString cf;
    QString name;
    QString surname;
    int sex; // 0 = male, 1 = female
    QString birthday;
    unsigned int fk_birthplace;
    QString residence;
    QString email;
    QString phone;
};

#endif // PATIENT_H
