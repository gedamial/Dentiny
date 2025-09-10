#include "authenticationwindow.h"
#include "ui_authenticationwindow.h"
#include "credentialmodel.h"

AuthenticationWindow::AuthenticationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthenticationWindow)
{
    ui->setupUi(this);

    AuthResult = AuthenticationResult::Aborted;
}

AuthenticationWindow::~AuthenticationWindow()
{
    delete ui;
}

AuthenticationResult AuthenticationWindow::getAuthenticationResult()
{
    return AuthResult;
}

void AuthenticationWindow::on_btnCancel_clicked()
{
    AuthResult = AuthenticationResult::Aborted;

    reject();
}

void AuthenticationWindow::on_btnOK_clicked()
{
    CredentialModel m;
    QString input = ui->txtPassword->text();

    if(m.Authenticate(input))
    {
        AuthResult = AuthenticationResult::Success;
    }

    else
    {
        AuthResult = AuthenticationResult::Failed;

    }

    close();
}

