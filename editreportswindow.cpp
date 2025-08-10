#include "editreportswindow.h"
#include "ui_editreportswindow.h"
#include "model.h"
#include "reportitem.h"
#include "ui_reportitem.h"
#include <QPushButton>
#include <QDesktopServices>
#include <QFile>

EditReportsWindow::EditReportsWindow(QWidget *parent) : QDialog(parent), ui(new Ui::EditReportsWindow)
{
    ui->setupUi(this);

    Model m;

    // Pre-load patient combobox
    QList<Patient> patients = m.getAllPatientsSortedBySurname();

    for(int i = 0; i < patients.size(); ++i)
    {
        QString displayText = patients[i].surname + " " + patients[i].name + " - " + patients[i].cf;
        ui->cmbPatient->addItem(displayText);
    }

    // Register for updates
    Model::RegisterObserver(this, ObserverType::Reports);
}

EditReportsWindow::~EditReportsWindow()
{
    Model::UnregisterObserver(this, ObserverType::Reports);

    delete ui;
}

void EditReportsWindow::on_cmbPatient_currentIndexChanged(int index)
{
    UpdateReportsList();
}

void EditReportsWindow::UpdateReportsList()
{
    const QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();

    // Load patient reports
    Model m;
    Patient selectedPatient = m.getPatientFromCf(selectedPatientCf);

    QList<Report> reports = m.getReportsOfPatient(selectedPatient.id);

    QWidget* container = new QWidget();                    // Container for the ReportItems
    QVBoxLayout* layout = new QVBoxLayout(container);      // Layout to stack them vertically
    layout->setAlignment(Qt::AlignTop);
    container->setLayout(layout);

    for(int i = 0; i < reports.size(); ++i)
    {
        ReportItem* repItem = new ReportItem;
        SetupReportItem(repItem, reports[i]);

        QList<Attachment> reportAttachments = m.getAttachmentsOfReport(reports[i]);

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
    Model m;

    // Remove corresponding attachments from Reports folder
    QList<Attachment> attachments = m.getAttachmentsOfReport(report);

    for(int i = 0; i < attachments.size(); ++i)
    {
        const QString filePath = QCoreApplication::applicationDirPath() + "/Reports/" + QString::number(report.fk_patient) + "/" + attachments[i].filename;
        QFile::remove(filePath);

        m.deleteAttachment(attachments[i]);
    }

    m.deleteReport(report.id);
}

void EditReportsWindow::UpdateReport(ReportItem* reportItem, Report report)
{
    report.notes = reportItem->ui->txtNotes->toPlainText();

    Model m;
    m.updateReport(report);
}

void EditReportsWindow::OpenAttachment(const Attachment& attachment)
{
    Model m;
    Patient patient = m.getPatientFromId(m.getReportFromId(attachment.fk_report).fk_patient);

    const QString path = QCoreApplication::applicationDirPath() + "/Reports/"+QString::number(patient.id)+"/"+attachment.filename;
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void EditReportsWindow::on_btnClose_clicked()
{
    close();
}

