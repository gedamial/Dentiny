#ifndef CREDENTIALMODEL_H
#define CREDENTIALMODEL_H

#include <QString>
#include <QSqlDatabase>
#include "credentialdao.h"

class CredentialModel
{
public:
    CredentialModel();

    bool Authenticate(const QString& hashValue);
    QString GetCredential(const QString& name);
    void SetPassword(const QString& newPassword);

private:
    QSqlDatabase db;
    CredentialDAO credentialDao;
};

#endif // CREDENTIALMODEL_H
