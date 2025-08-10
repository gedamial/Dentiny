#include "addreportwindow.h"
#include "ui_addreportwindow.h"
#include "authenticationwindow.h"
#include "model.h"
#include "report.h"
#include "attachment.h"
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
    QFileDialog uploadDialog(this);
    uploadDialog.setFileMode(QFileDialog::ExistingFiles);
    uploadDialog.setViewMode(QFileDialog::Detail);

    if (uploadDialog.exec())
    {
        uploadedFilePaths.append(uploadDialog.selectedFiles());

        QString labelStr;

        for(int i = 0; i < uploadedFilePaths.size(); ++i)
        {
            QFileInfo fileInfo(uploadedFilePaths[i]);

            labelStr += fileInfo.fileName() + "\n";
        }

        ui->lblUploadedFiles->setText(labelStr);
    }
}

void AddReportWindow::on_btnOK_clicked()
{
    Model m;
    const QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    const Patient selectedPatient = m.getPatientFromCf(selectedPatientCf);
    const QString patientIdString = QString::number(selectedPatient.id);

    QString fileNames;

    QList<Attachment> attachments;

    // Upload files by copying them into the patient-dedicated folder
    for(int i = 0; i < uploadedFilePaths.size(); ++i)
    {
        const QFileInfo currentFileInfo(uploadedFilePaths[i]);
        const QString fileName = currentFileInfo.fileName();
        const QString destinationDir = QCoreApplication::applicationDirPath() + "/Reports/" + patientIdString;

        QDir directory(destinationDir);

        if(!directory.exists())
        {
            directory.mkpath(destinationDir);
        }

        const QString destinationPath = destinationDir + "/" + fileName;
        QFile::copy(uploadedFilePaths[i], destinationPath);

        fileNames += fileName+";";

        // Add attachment in the database
        Attachment newAttachment;
        newAttachment.filename = fileName;
        attachments.append(newAttachment);
    }

    // Add report in the database
    Report newReport;
    newReport.datetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
    newReport.notes = ui->txtNotes->toPlainText();
    newReport.fk_patient = selectedPatient.id;
    const int reportId = m.insertReport(newReport);

    // Add attachments in the database
    for(int i = 0; i < attachments.size(); ++i)
    {
        attachments[i].fk_report = reportId;
        m.insertAttachment(attachments[i]);
    }

    close();
}

