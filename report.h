#ifndef REPORT_H
#define REPORT_H

#include <QString>

class Report
{
public:
    Report();

    int id;
    QString datetime;
    QString notes;
    QString filenames;
    int fk_patient;
};

#endif // REPORT_H
