#include "reportdao.h"
#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

ReportDAO::ReportDAO() {}

int ReportDAO::insertReport(const Report& report)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Report (datetime, notes, fk_patient) VALUES (:datetime, :notes, :fk_patient)");
    query.bindValue(":datetime", report.datetime);
    query.bindValue(":notes", report.notes);
    query.bindValue(":fk_patient", report.fk_patient);
    query.exec();

    return query.lastInsertId().toInt();
}

Report ReportDAO::LoadFromQueryRow(const QSqlQuery &query)
{
    Report rep;
    rep.id = query.value("id").toInt();
    rep.datetime = query.value("datetime").toString();
    rep.notes = query.value("notes").toString();
    rep.fk_patient = query.value("fk_patient").toInt();

    return rep;
}

Report ReportDAO::getReportFromId(int id)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Report WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    return LoadFromQueryRow(query);
}

QList<Report> ReportDAO::getReportsOfPatient(int patientId)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Report WHERE fk_patient = :fk_patient");
    query.bindValue(":fk_patient", patientId);

    QList<Report> reports;

    if(query.exec())
    {
        while (query.next())
        {
            Report rep = LoadFromQueryRow(query);
            reports.append(rep);
        }
    }

    else
    {
        // print error
        qDebug() << "query exec error in ReportDAO::getReportsOfPatient";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }

    return reports;
}

void ReportDAO::deleteReport(int id)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM Report WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void ReportDAO::updateReport(const Report& newReport)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("UPDATE Report SET datetime=:datetime, notes=:notes, fk_patient=:fk_patient WHERE id = :id");
    query.bindValue(":datetime", newReport.datetime);
    query.bindValue(":notes", newReport.notes);
    query.bindValue(":fk_patient", newReport.fk_patient);
    query.bindValue(":id", newReport.id);

    if(!query.exec())
    {
        // print error
        qDebug() << "query exec error in ReportDAO::updateReport";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }
}
