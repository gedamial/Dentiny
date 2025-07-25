#include "addappointmentwindow.h"
#include "ui_addappointmentwindow.h"
#include "patientdao.h"
#include "patient.h"
#include "appointmentdao.h"
#include "appointment.h"
#include "statusdao.h"
#include "status.h"
#include <QList>
#include <QMessageBox>

AddAppointmentWindow::AddAppointmentWindow(const QDate defaultDate, QWidget *parent) : QDialog(parent), ui(new Ui::AddAppointmentWindow)
{
    ui->setupUi(this);

    // Pre-load patient combobox
    PatientDAO patientDao;
    QList<Patient> patients = patientDao.getAllPatientsSorted();

    for(int i = 0; i < patients.size(); ++i)
    {
        QString displayText = patients[i].surname + " " + patients[i].name + " - " + patients[i].cf;
        ui->cmbPatient->addItem(displayText);
    }

    // Pre-load datetime widget
    ui->dateTimeEdit->setDate(defaultDate);
    ui->dateTimeEdit->setTime(QTime::currentTime());

    // Pre-load with appointment statuses
    StatusDAO statusDao;
    QList<Status> statuses = statusDao.getAllStatuses();

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
    QMessageBox msgBox;

    if(ui->cmbPatient->currentIndex() == -1)
    {
        msgBox.setInformativeText("Please select a patient from the list.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    else if(ui->dateTimeEdit->dateTime() < QDateTime::currentDateTime())
    {
        msgBox.setInformativeText("Cannot create an appointment in the past.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    else
    {
        PatientDAO patientDao;
        QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
        Patient selectedPatient = patientDao.getPatientFromCf(selectedPatientCf);

        Appointment newApp;
        newApp.datetime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm");
        newApp.reason = ui->txtReason->toPlainText();
        newApp.fk_status = ui->cmbStatus->currentIndex();
        newApp.fk_patient = selectedPatient.id;

        AppointmentDAO appDao;
        appDao.insertAppointment(newApp);

        close();
    }
}

