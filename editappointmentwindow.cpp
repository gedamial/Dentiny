#include "editappointmentwindow.h"
#include "ui_editappointmentwindow.h"
#include "patient.h"
#include "status.h"
#include "model.h"

EditAppointmentWindow::EditAppointmentWindow(unsigned int appointmentID, QWidget *parent) : QDialog(parent), ui(new Ui::EditAppointmentWindow), appointmentID{appointmentID}
{
    ui->setupUi(this);

    Model m;

    associatedAppointment = m.getAppointmentFromId(appointmentID);

    // Load patient combobox
    QList<Patient> patients = m.getAllPatientsSortedBySurname();
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
    QList<Status> statuses = m.getAllStatuses();

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
    Model m;

    // Get the id of the selected Patient
    QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    Patient selectedPatient = m.getPatientFromCf(selectedPatientCf);

    Appointment newApp;
    newApp.id = associatedAppointment.id;
    newApp.fk_patient = selectedPatient.id;
    newApp.datetime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm");
    newApp.reason = ui->txtReason->toPlainText();
    newApp.fk_status = ui->cmbStatus->currentIndex();

    m.updateAppointmentWithId(appointmentID, newApp);

    close();
}

