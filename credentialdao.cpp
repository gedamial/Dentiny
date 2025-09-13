#include "credentialdao.h"
#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

CredentialDAO::CredentialDAO() {}

QString CredentialDAO::getCredential(const QString &name)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT value FROM Credential WHERE name = :name");
    query.bindValue(":name", name);
    query.exec();
    query.next();

    return query.value("value").toString();
}

void CredentialDAO::updateCredential(const QString &name, const QString &newValue)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    QSqlQuery query(db);
    query.prepare("UPDATE Credential SET value = :new_value WHERE name = :credential_name");
    query.bindValue(":credential_name", name);
    query.bindValue(":new_value", newValue);
    query.exec();
}


