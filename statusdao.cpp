#include "statusdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "dbmanager.h"

StatusDAO::StatusDAO() {}

QString StatusDAO::getStatusNameFromId(int id)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT name FROM Status WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    return query.value("name").toString();
}

QList<Status> StatusDAO::getAllStatuses()
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query("SELECT * FROM Status");

    QList<Status> statuses;

    if(query.exec())
    {
        while(query.next())
        {
            Status s;
            s.id = query.value("id").toInt();
            s.name = query.value("name").toString();

            statuses.append(s);
        }
    }

    else
    {
        // print error
        qDebug() << "query exec error in PlaceDAO::getAllPlaces";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }

    return statuses;
}

