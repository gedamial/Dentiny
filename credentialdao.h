#ifndef CREDENTIALDAO_H
#define CREDENTIALDAO_H

#include <QString>

class CredentialDAO
{
public:
    CredentialDAO();

    QString getCredential(const QString& name);
    void updateCredential(const QString& name, const QString& newValue);
};

#endif // CREDENTIALDAO_H
