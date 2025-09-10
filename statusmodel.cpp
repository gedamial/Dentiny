#include "statusmodel.h"

StatusModel::StatusModel() {}

QString StatusModel::getStatusNameFromId(int id)
{
    return statusDao.getStatusNameFromId(id);
}

QList<Status> StatusModel::getAllStatuses()
{
    return statusDao.getAllStatuses();
}
