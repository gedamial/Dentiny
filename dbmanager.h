#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>

class DBManager
{
public:
    static DBManager getInstance();
    QSqlDatabase getDatabase();

    ~DBManager();

private:
    DBManager();

    QSqlDatabase database;
};

#endif // DBMANAGER_H
