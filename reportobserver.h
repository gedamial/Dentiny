#ifndef REPORTOBSERVER_H
#define REPORTOBSERVER_H

class ReportObserver
{
public:
    ReportObserver();

    virtual void UpdateReports() = 0;
};

#endif // REPORTOBSERVER_H
