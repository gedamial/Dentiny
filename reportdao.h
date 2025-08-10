#ifndef REPORTDAO_H
#define REPORTDAO_H

#include "report.h"
#include <QSqlQuery>

class ReportDAO
{
public:
    ReportDAO();

    int insertReport(const Report& report);
    Report LoadFromQueryRow(const QSqlQuery& query);
    Report getReportFromId(int id);
    QList<Report> getReportsOfPatient(int patientId);
    void deleteReport(int id);
    void updateReport(const Report& newReport);
};

#endif // REPORTDAO_H
