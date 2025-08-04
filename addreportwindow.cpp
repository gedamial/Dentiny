#include "addreportwindow.h"
#include "ui_addreportwindow.h"
#include "authenticationwindow.h"
#include "model.h"
#include "report.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>

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

void AddReportWindow::on_btnUpload_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);

    if (dialog.exec())
    {
        uploadedFilePaths = dialog.selectedFiles();

        for(int i = 0; i < uploadedFilePaths.size(); ++i)
        {
            QFileInfo fileInfo(uploadedFilePaths[i]);

            ui->lblUploadedFiles->setText(ui->lblUploadedFiles->text() + fileInfo.fileName() + "\n");
        }
    }
}

void AddReportWindow::on_btnOK_clicked()
{
    Model m;
    const QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    const Patient selectedPatient = m.getPatientFromCf(selectedPatientCf);
    const QString patientIdString = QString::number(selectedPatient.id);

    QString fileNames;

    // Upload files by copying them into the patient-dedicated folder
    for(int i = 0; i < uploadedFilePaths.size(); ++i)
    {
        const QFileInfo currentFileInfo(uploadedFilePaths[i]);
        const QString fileName = currentFileInfo.fileName();
        const QString destinationDir = "./" + patientIdString;

        QDir directory(destinationDir);

        if(!directory.exists())
        {
            directory.mkdir(".");
        }

        const QString destinationPath = destinationDir + "/" + fileName;
        QFile::copy(uploadedFilePaths[i], destinationPath);

        fileNames += fileName+";";
    }

    // Add report in the database
    Report newReport;
    newReport.datetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
    newReport.notes = ui->txtNotes->toPlainText();
    newReport.filenames = fileNames;
    newReport.fk_patient = selectedPatient.id;

    m.insertReport(newReport);

    close();
}

