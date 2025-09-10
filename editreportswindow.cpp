#include "editreportswindow.h"
#include "ui_editreportswindow.h"
#include "patientmodel.h"
#include "reportmodel.h"
#include "attachmentmodel.h"
#include "reportitem.h"
#include "ui_reportitem.h"
#include "authenticationwindow.h"
#include <QPushButton>
#include <QDesktopServices>
#include <QFile>
#include <QMessageBox>

EditReportsWindow::EditReportsWindow(QWidget *parent) : QDialog(parent), ui(new Ui::EditReportsWindow)
{
    ui->setupUi(this);

    PatientModel pm;

    // Pre-load patient combobox
    QList<Patient> patients = pm.getAllPatientsSortedBySurname();

    for(int i = 0; i < patients.size(); ++i)
    {
        QString displayText = patients[i].surname + " " + patients[i].name + " - " + patients[i].cf;
        ui->cmbPatient->addItem(displayText);
    }

    // Register for updates
    ReportModel rm;
    rm.RegisterObserver(this);
}

EditReportsWindow::~EditReportsWindow()
{
    ReportModel rm;
    rm.UnregisterObserver(this);

    delete ui;
}

int EditReportsWindow::exec()
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

void EditReportsWindow::on_cmbPatient_currentIndexChanged(int index)
{
    UpdateReportsList();
}

void EditReportsWindow::UpdateReportsList()
{
    const QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();

    // Load patient reports
    PatientModel pm;
    ReportModel rm;
    AttachmentModel am;

    Patient selectedPatient = pm.getPatientFromCf(selectedPatientCf);

    QList<Report> reports = rm.getReportsOfPatient(selectedPatient.id);

    QWidget* container = new QWidget();                    // Container for the ReportItems
    QVBoxLayout* layout = new QVBoxLayout(container);      // Layout to stack them vertically
    layout->setAlignment(Qt::AlignTop);
    container->setLayout(layout);

    for(int i = 0; i < reports.size(); ++i)
    {
        ReportItem* repItem = new ReportItem;
        SetupReportItem(repItem, reports[i]);

        QList<Attachment> reportAttachments = am.getAttachmentsOfReport(reports[i]);

        for(int j = 0; j < reportAttachments.size(); ++j)
        {
            QPushButton* btn = new QPushButton;
            btn->setText(reportAttachments[j].filename);
            btn->setFlat(true);
            connect(btn, &QPushButton::clicked, this, [=]() { OpenAttachment(reportAttachments[j]); });

            repItem->ui->lytAttachments->addWidget(btn);
        }

        layout->addWidget(repItem);  // Add to the layout
    }

    ui->scrollArea->setWidget(container);
}

void EditReportsWindow::UpdateReports()
{
    UpdateReportsList();
}

void EditReportsWindow::SetupReportItem(ReportItem* reportItem, Report report)
{
    reportItem->ui->lblDatetime->setText(report.datetime);
    reportItem->ui->txtNotes->setPlainText(report.notes);
    connect(reportItem->ui->btnRemove, &QPushButton::clicked, this, [=]() { RemoveReport(report); });
    connect(reportItem->ui->btnApply, &QPushButton::clicked, this, [=]() { UpdateReport(reportItem, report); });
}

void EditReportsWindow::RemoveReport(Report report)
{
    ReportModel rm;
    AttachmentModel am;

    // Remove corresponding attachments from Reports folder
    QList<Attachment> attachments = am.getAttachmentsOfReport(report);

    for(int i = 0; i < attachments.size(); ++i)
    {
        const QString filePath = QCoreApplication::applicationDirPath() + "/Reports/" + QString::number(report.fk_patient) + "/" + attachments[i].filename;
        QFile::remove(filePath);

        am.deleteAttachment(attachments[i]);
    }

    rm.deleteReport(report.id);
}

void EditReportsWindow::UpdateReport(ReportItem* reportItem, Report report)
{
    report.notes = reportItem->ui->txtNotes->toPlainText();

    ReportModel rm;
    rm.updateReport(report);
}

void EditReportsWindow::OpenAttachment(const Attachment& attachment)
{
    PatientModel pm;
    ReportModel rm;
    Patient patient = pm.getPatientFromId(rm.getReportFromId(attachment.fk_report).fk_patient);

    const QString path = QCoreApplication::applicationDirPath() + "/Reports/"+QString::number(patient.id)+"/"+attachment.filename;
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void EditReportsWindow::on_btnClose_clicked()
{
    close();
}

