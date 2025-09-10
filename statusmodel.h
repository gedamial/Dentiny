#ifndef STATUSMODEL_H
#define STATUSMODEL_H

#include "status.h"
#include "statusdao.h"

#include <QList>
#include <QString>

class StatusModel
{
public:
    StatusModel();

    QString getStatusNameFromId(int id);
    QList<Status> getAllStatuses();

private:
    StatusDAO statusDao;
};

#endif // STATUSMODEL_H
