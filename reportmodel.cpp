#include "reportmodel.h"

QVector<ReportObserver*> ReportModel::ReportObservers;

ReportModel::ReportModel() {}

int ReportModel::insertReport(const Report &report)
{
    int result = reportDao.insertReport(report);

    ReportModel::UpdateObservers();

    return result;
}

QList<Report> ReportModel::getReportsOfPatient(int patientId)
{
    return reportDao.getReportsOfPatient(patientId);
}

Report ReportModel::getReportFromId(int id)
{
    return reportDao.getReportFromId(id);
}

void ReportModel::deleteReport(int id)
{
    reportDao.deleteReport(id);

    ReportModel::UpdateObservers();
}

void ReportModel::updateReport(const Report &report)
{
    reportDao.updateReport(report);
    ReportModel::UpdateObservers();
}

void ReportModel::RegisterObserver(ReportObserver* newObserver)
{
    ReportModel::ReportObservers.append(newObserver);
}

void ReportModel::UpdateObservers()
{
    for(int i = 0; i < ReportModel::ReportObservers.size(); ++i)
    {
        ReportModel::ReportObservers[i]->UpdateReports();
    }
}

void ReportModel::UnregisterObserver(ReportObserver* observer)
{
    ReportModel::ReportObservers.removeOne(observer);
}
