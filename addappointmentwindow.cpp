#include "addappointmentwindow.h"
#include "ui_addappointmentwindow.h"
#include "patientdao.h"
#include "patient.h"
#include "appointmentdao.h"
#include "appointment.h"
#include <QList>
#include <QMessageBox>

AddAppointmentWindow::AddAppointmentWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddAppointmentWindow)
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

    // Pre-load datetime widget with current datetime
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
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
        QString patientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
        Patient p = patientDao.getPatientFromCf(patientCf);

        Appointment newApp;
        newApp.datetime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm");
        newApp.reason = ui->txtReason->toPlainText();
        newApp.status = 0;
        newApp.fk_patient = p.id;

        AppointmentDAO appDao;
        appDao.insertAppointment(newApp);

        close();
    }
}

