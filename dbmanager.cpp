#include "dbmanager.h"

#include <QSqlError>
#include <QDir>
#include <QSqlQuery>
#include <QApplication>

DBManager::DBManager()
{
    bool initializeDatabase = false;

    database = QSqlDatabase::addDatabase("QSQLITE");

    if(!QFile::exists("dentinydb.db"))
        initializeDatabase = true;

    database.setDatabaseName("dentinydb.db");
    database.open();

    if(initializeDatabase)
        InitializeDatabase();
}

void DBManager::InitializeDatabase()
{
    QFile schemaFile(":/resources/sql/schema.sql");

    if (!schemaFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error loading SQL schema file!" << schemaFile.errorString();
        QApplication::quit();
    }

    QTextStream in(&schemaFile);
    QString schemaSql = in.readAll();
    schemaFile.close();

    // Split the script into individual queries
    // Use a regular expression to split by semicolon, ignoring empty parts
    QStringList queries = schemaSql.split(';', Qt::SkipEmptyParts);

    // Execute each query
    QSqlQuery query(database);

    for (const QString& sqlQuery : queries)
    {
        // Trim whitespace from the query string
        QString trimmedQuery = sqlQuery.trimmed();

        if (trimmedQuery.isEmpty())
        {
            continue;
        }

        if (!query.exec(trimmedQuery))
        {
            qDebug() << "Error executing query:" << query.lastError().text();
            qDebug() << "Query was:" << trimmedQuery;

            QApplication::quit();
        }
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
}
