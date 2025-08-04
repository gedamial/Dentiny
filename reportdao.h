#ifndef REPORTDAO_H
#define REPORTDAO_H

#include "report.h"

class ReportDAO
{
public:
    ReportDAO();

    bool insertReport(const Report& report);
};

#endif // REPORTDAO_H
