#include "addreportwindow.h"
#include "ui_addreportwindow.h"
#include "authenticationwindow.h"
#include "model.h"
#include <QMessageBox>

AddReportWindow::AddReportWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddReportWindow)
{
    ui->setupUi(this);

    // Pre-load patient combobox
    Model m;
    QList<Patient> patients = m.getAllPatientsSortedBySurname();

    for(int i = 0; i < patients.size(); ++i)
    {
        QString displayText = patients[i].surname + " " + patients[i].name + " - " + patients[i].cf;
        ui->cmbPatient->addItem(displayText);
    }
}

int AddReportWindow::exec()
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
        QMessageBox msgBox;
        msgBox.setInformativeText("Authentication failed!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        close();
    }

    else if(result == AuthenticationResult::Aborted)
    {
        close();
    }

    return -1;
}

AddReportWindow::~AddReportWindow()
{
    delete ui;
}

void AddReportWindow::on_btnCancel_clicked()
{
    close();
}

