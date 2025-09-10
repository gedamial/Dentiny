#ifndef REPORTMODEL_H
#define REPORTMODEL_H
#include "report.h"
#include "reportdao.h"
#include "reportobserver.h"

#include <QList>
#include <QString>

class ReportModel
{
public:
    ReportModel();

    int insertReport(const Report& report);
    QList<Report> getReportsOfPatient(int patientId);
    Report getReportFromId(int id);
    void deleteReport(int id);
    void updateReport(const Report& newReport);

    void RegisterObserver(ReportObserver* newObserver);
    void UpdateObservers();
    void UnregisterObserver(ReportObserver* observer);

private:
    ReportDAO reportDao;
    static QVector<ReportObserver*> ReportObservers;
};

#endif // REPORTMODEL_H
