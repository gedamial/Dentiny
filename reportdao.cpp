#include "reportdao.h"
#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>

ReportDAO::ReportDAO() {}

bool ReportDAO::insertReport(const Report& report)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Report (datetime, notes, filenames, fk_patient) VALUES (:datetime, :notes, :filenames, :fk_patient)");
    query.bindValue(":datetime", report.datetime);
    query.bindValue(":notes", report.notes);
    query.bindValue(":filenames", report.filenames);
    query.bindValue(":fk_patient", report.fk_patient);

    return query.exec();
}
