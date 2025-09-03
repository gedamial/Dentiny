#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DBManager
{
public:
    static DBManager getInstance();
    QSqlDatabase getDatabase();

    ~DBManager();

private:
    DBManager();

    QSqlDatabase database;
    void InitializeDatabase();
};

#endif // DBMANAGER_H
