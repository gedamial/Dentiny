#include "addreportwindow.h"
#include "ui_addreportwindow.h"
#include "authenticationwindow.h"
#include "patientmodel.h"
#include "reportmodel.h"
#include "attachmentmodel.h"
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
    PatientModel pm;
    QList<Patient> patients = pm.getAllPatientsSortedBySurname();

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
        QMessageBox::warning(this, "Authentication failed", "Authentication failed!", QMessageBox::Ok);
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
    PatientModel pm;
    ReportModel rm;
    AttachmentModel am;

    const QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    const Patient selectedPatient = pm.getPatientFromCf(selectedPatientCf);
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
    const int reportId = rm.insertReport(newReport);

    // Add attachments in the database
    for(int i = 0; i < attachments.size(); ++i)
    {
        attachments[i].fk_report = reportId;
        am.insertAttachment(attachments[i]);
    }

    close();
}

