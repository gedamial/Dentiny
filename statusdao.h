#ifndef STATUSDAO_H
#define STATUSDAO_H

#include "status.h"
#include <QList.h>

class StatusDAO
{
public:
    StatusDAO();

    QString getNameFromId(int id);
    QList<Status> getAllStatuses();
};

#endif // STATUSDAO_H
