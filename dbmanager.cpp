#include "dbmanager.h"

#include <QSqlError>
#include <QDir>

DBManager::DBManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("../../dentinydb.db");

    // Connection to the database failed!
    if(!database.open())
    {
        qDebug() << "COULD NOT CONNECT TO DATABASE!";
        qDebug() << database.lastError().type();     // Error type (e.g. ConnectionError)
        qDebug() << database.lastError().nativeErrorCode();   // Driver error code
        qDebug() << database.lastError().driverText(); // Driver error description
        qDebug() << database.lastError().databaseText(); // Detailed DB error

        qDebug() << "Current Path:" << QDir::currentPath();
        qDebug() << "Database Path:" << QFileInfo("../../dentinydb.db").absoluteFilePath();
    }
}

DBManager DBManager::getInstance()
{
    static DBManager instance;

    return instance;
}

QSqlDatabase DBManager::getDatabase()
{
    return database;
}

DBManager::~DBManager()
{
    /*
    qDebug() << "destr called";
    database.close();
    */
}
