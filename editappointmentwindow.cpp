#include "editappointmentwindow.h"
#include "ui_editappointmentwindow.h"
#include "appointmentdao.h"
#include "patient.h"
#include "patientdao.h"
#include "status.h"
#include "statusdao.h"

EditAppointmentWindow::EditAppointmentWindow(unsigned int appointmentID, QWidget *parent) : QDialog(parent), ui(new Ui::EditAppointmentWindow), appointmentID{appointmentID}
{
    ui->setupUi(this);

    AppointmentDAO appDao;
    associatedAppointment = appDao.getAppointmentFromId(appointmentID);

    // Load patient combobox
    PatientDAO patientDao;
    QList<Patient> patients = patientDao.getAllPatientsSorted();
    int currentPatientIndex;

    for(int i = 0; i < patients.size(); ++i)
    {
        QString displayText = patients[i].surname + " " + patients[i].name + " - " + patients[i].cf;
        ui->cmbPatient->addItem(displayText);

        if(patients[i].id == associatedAppointment.fk_patient)
            currentPatientIndex = i;
    }

    ui->cmbPatient->setCurrentIndex(currentPatientIndex);

    // Load datetime widget
    QDateTime appDatetime = QDateTime::fromString(associatedAppointment.datetime, "yyyy-MM-dd hh:mm");
    ui->dateTimeEdit->setDateTime(appDatetime);

    // Load reason
    ui->txtReason->setPlainText(associatedAppointment.reason);

    // Load appointment statuses
    StatusDAO statusDao;
    QList<Status> statuses = statusDao.getAllStatuses();

    for(int i = 0; i < statuses.size(); ++i)
    {
        ui->cmbStatus->addItem(statuses[i].name);
    }

    ui->cmbStatus->setCurrentIndex(associatedAppointment.fk_status);
}

EditAppointmentWindow::~EditAppointmentWindow()
{
    delete ui;
}

void EditAppointmentWindow::on_btnCancel_clicked()
{
    close();
}


void EditAppointmentWindow::on_btnSave_clicked()
{
    PatientDAO patientDao;
    AppointmentDAO appDao;

    // Get the id of the selected Patient
    QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    Patient selectedPatient = patientDao.getPatientFromCf(selectedPatientCf);

    Appointment newApp;
    newApp.id = associatedAppointment.id;
    newApp.fk_patient = selectedPatient.id;
    newApp.datetime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm");
    newApp.reason = ui->txtReason->toPlainText();
    newApp.fk_status = ui->cmbStatus->currentIndex();

    appDao.UpdateAppointmentWithId(appointmentID, newApp);

    close();
}

