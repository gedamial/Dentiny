#include "setpasswordwindow.h"
#include "ui_setpasswordwindow.h"
#include "authenticationwindow.h"
#include "credentialmodel.h"
#include <QMessageBox>

SetPasswordWindow::SetPasswordWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SetPasswordWindow)
{
    ui->setupUi(this);
}

int SetPasswordWindow::exec()
{
    AuthenticationWindow auth_wndw;
    auth_wndw.exec();

    const AuthenticationResult result = auth_wndw.getAuthenticationResult();

    if(result == AuthenticationResult::Success)
    {
        return QDialog::exec();
    }

    else if(result == AuthenticationResult::Failed)
    {
        QMessageBox::warning(this, "Authentication failed", "Authentication failed!", QMessageBox::Ok);
        close();
    }

    else if(result == AuthenticationResult::Aborted)
    {
        close();
    }

    return -1;
}

SetPasswordWindow::~SetPasswordWindow()
{
    delete ui;
}

void SetPasswordWindow::on_btnCancel_clicked()
{
    close();
}

void SetPasswordWindow::on_btnOK_clicked()
{
    const QString psw1 = ui->txtPassword1->text();
    const QString psw2 = ui->txtPassword2->text();

    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    if(psw1 != psw2)
    {
        msgBox.setInformativeText("The two passwords are different!");
        msgBox.exec();
    }

    else
    {
        CredentialModel m;
        m.SetPassword(psw1);

        close();
    }
}

