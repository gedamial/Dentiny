#ifndef PATIENT_H
#define PATIENT_H
#include <QString>

class Patient
{
public:
    Patient();

    /*
    void setId(unsigned int id);
    void setCf(QString cf);
    void setName(QString name);
    void setSurname(QString surname);
    void setSex(bool sex);
    void setBirthday(QString birthday);
    void setBirthplace(unsigned int fk_birthplace);
    void setResidence(QString residence);
    void setEmail(QString email);
    void setPhone(QString phone);
    */

    unsigned int id;
    QString cf;
    QString name;
    QString surname;
    bool sex; // 0 = male, 1 = female
    QString birthday;
    unsigned int fk_birthplace;
    QString residence;
    QString email;
    QString phone;
};

#endif // PATIENT_H
