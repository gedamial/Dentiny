#include "addappointmentwindow.h"
#include "ui_addappointmentwindow.h"
#include "patient.h"
#include "appointment.h"
#include "status.h"
#include "patientmodel.h"
#include "statusmodel.h"
#include "appointmentmodel.h"
#include <QList>
#include <QMessageBox>

AddAppointmentWindow::AddAppointmentWindow(const QDate defaultDate, QWidget *parent) : QDialog(parent), ui(new Ui::AddAppointmentWindow)
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

    // Pre-load datetime widget
    ui->dateTimeEdit->setDate(defaultDate);
    ui->dateTimeEdit->setTime(QTime::currentTime());

    // Pre-load with appointment statuses
    StatusModel sm;
    QList<Status> statuses = sm.getAllStatuses();

    for(int i = 0; i < statuses.size(); ++i)
    {
        ui->cmbStatus->addItem(statuses[i].name);
    }
}

AddAppointmentWindow::~AddAppointmentWindow()
{
    delete ui;
}

void AddAppointmentWindow::on_btnCancel_clicked()
{
    close();
}

void AddAppointmentWindow::on_btnConfirm_clicked()
{
    if(ui->cmbPatient->currentIndex() == -1)
    {
        QMessageBox::warning(this, "No patient selected", "Please select a patient from the list.", QMessageBox::Ok);
    }

    else if(ui->dateTimeEdit->dateTime() < QDateTime::currentDateTime())
    {
        QMessageBox::warning(this, "Invalid date", "Cannot create an appointment in the past.", QMessageBox::Ok);
    }

    else
    {
        PatientModel pm;
        AppointmentModel am;

        QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
        Patient selectedPatient = pm.getPatientFromCf(selectedPatientCf);

        Appointment newApp;
        newApp.datetime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm");
        newApp.reason = ui->txtReason->toPlainText();
        newApp.fk_status = ui->cmbStatus->currentIndex();
        newApp.fk_patient = selectedPatient.id;

        am.insertAppointment(newApp);

        close();
    }
}
