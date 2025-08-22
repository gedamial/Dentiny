#ifndef CREDENTIALDAO_H
#define CREDENTIALDAO_H

#include <QString>

class CredentialDAO
{
public:
    CredentialDAO();

    QString getCredential(const QString& name);
};

#endif // CREDENTIALDAO_H
