#include "credentialmodel.h"
#include <QSqlQuery>
#include <QCryptographicHash>

CredentialModel::CredentialModel() {}

bool CredentialModel::Authenticate(const QString& plaintext)
{
    const QString truePassword = credentialDao.getCredential("dentist_password");
    const QByteArray hashedValue = QCryptographicHash::hash(plaintext.toUtf8(), QCryptographicHash::Sha256);

    if(hashedValue.toHex() == truePassword)
    {
        return true;
    }

    return false;
}

QString CredentialModel::GetCredential(const QString &name)
{
    return credentialDao.getCredential(name);
}

void CredentialModel::SetPassword(const QString &newPassword)
{
    const QString newPasswordHashed = QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Sha256).toHex();

    credentialDao.updateCredential("dentist_password", newPasswordHashed);
}
