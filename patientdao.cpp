#include "patientdao.h"
#include "dbmanager.h"
#include <QSqlQuery>

PatientDAO::PatientDAO() {}

bool PatientDAO::insertPatient(const Patient& patient)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Patient (cf, name, surname, sex, birthday, fk_birthplace, residence, email, phone) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(patient.cf);
    query.addBindValue(patient.name);
    query.addBindValue(patient.surname);
    query.addBindValue(patient.sex);
    query.addBindValue(patient.birthday);
    query.addBindValue(patient.fk_birthplace);
    query.addBindValue(patient.residence);
    query.addBindValue(patient.email);
    query.addBindValue(patient.phone);
    return query.exec();
}

Patient PatientDAO::getPatientFromId(unsigned int id)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Patient WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    Patient newPatient;

    if(query.next())
    {
        newPatient.id = query.value(0).toInt();
        newPatient.cf = query.value(1).toString();
        newPatient.name = query.value(2).toString();
        newPatient.surname = query.value(3).toString();
        newPatient.sex = query.value(4).toBool();
        newPatient.birthday = query.value(5).toString();
        newPatient.fk_birthplace = query.value(6).toInt();
        newPatient.residence = query.value(7).toString();
        newPatient.email = query.value(8).toString();
        newPatient.phone = query.value(9).toString();
    }

    return newPatient;
}

Patient PatientDAO::getPatientFromCf(const QString& cf)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Patient WHERE cf = :cf");
    query.bindValue(":cf", cf);
    query.exec();

    Patient newPatient;

    if(query.next())
    {
        newPatient.id = query.value(0).toInt();
        newPatient.cf = query.value(1).toString();
        newPatient.name = query.value(2).toString();
        newPatient.surname = query.value(3).toString();
        newPatient.sex = query.value(4).toBool();
        newPatient.birthday = query.value(5).toString();
        newPatient.fk_birthplace = query.value(6).toInt();
        newPatient.residence = query.value(7).toString();
        newPatient.email = query.value(8).toString();
        newPatient.phone = query.value(9).toString();
    }

    return newPatient;
}

QList<Patient> PatientDAO::getAllPatients()
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();

    QList<Patient> patients;
    QSqlQuery query("SELECT id FROM Patient", db);

    while (query.next())
    {
        Patient newPatient = getPatientFromId(query.value(0).toInt());
        patients.append(newPatient);
    }

    return patients;
}

QList<Patient> PatientDAO::getAllPatientsSorted()
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();

    QList<Patient> patients;
    QSqlQuery query("SELECT id FROM Patient ORDER BY surname", db);

    while (query.next())
    {
        Patient newPatient = getPatientFromId(query.value(0).toInt());
        patients.append(newPatient);
    }

    return patients;
}
