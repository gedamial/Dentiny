#include "placedao.h"
#include <QSqlDatabase>
#include "dbmanager.h"
#include <QSqlQuery>

#include <QSqlError>

PlaceDAO::PlaceDAO() {}

Place PlaceDAO::getPlaceFromId(unsigned int id)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Place WHERE id = :id");
    query.bindValue(":id", id);

    Place newPlace;

    if(query.exec())
    {
        query.next();
        newPlace.id = query.value(0).toInt();
        newPlace.name = query.value(1).toString();
        newPlace.abbreviation = query.value(2).toString();
        newPlace.belfiore = query.value(3).toString();
    }

    else
    {
        // print error
        qDebug() << "query exec error in PlaceDAO::getPlaceFromId";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
    }

    return newPlace;
}

int PlaceDAO::getIdFromBelfiore(const QString &belfiore)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id FROM Place WHERE belfiore = :belfiore");
    query.bindValue(":belfiore", belfiore);

    if(query.exec())
    {
        query.next();
        return query.value(0).toInt();
    }

    else
    {
        // print error
        qDebug() << "query exec error in PlaceDAO::getPlaceFromId";
        qDebug() << query.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << query.lastError().nativeErrorCode();   // Driver error code
        qDebug() << query.lastError().driverText(); // Driver error description
        qDebug() << query.lastError().databaseText(); // Detailed DB error
        return -1;
    }
}


QList<Place> PlaceDAO::getAllPlaces()
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query("SELECT id FROM Place", db);

    QList<Place> places;

    if(query.exec())
    {
        while (query.next())
        {
            Place newPlace = getPlaceFromId(query.value(0).toInt());
            places.append(newPlace);
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

    return places;
}
