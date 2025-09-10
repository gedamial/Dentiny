#include "editappointmentwindow.h"
#include "ui_editappointmentwindow.h"
#include "patient.h"
#include "status.h"
#include "patientmodel.h"
#include "credentialmodel.h"
#include "appointmentmodel.h"
#include "statusmodel.h"

#include "SmtpClient/emailaddress.h"
#include "SmtpClient/mimemessage.h"
#include "SmtpClient/mimetext.h"
#include "SmtpClient/smtpclient.h"

EditAppointmentWindow::EditAppointmentWindow(unsigned int appointmentID, QWidget *parent) : QDialog(parent), ui(new Ui::EditAppointmentWindow), appointmentID{appointmentID}
{
    ui->setupUi(this);

    PatientModel pm;
    AppointmentModel am;
    StatusModel sm;

    associatedAppointment = am.getAppointmentFromId(appointmentID);

    // Load patient combobox
    QList<Patient> patients = pm.getAllPatientsSortedBySurname();
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
    QList<Status> statuses = sm.getAllStatuses();

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
    PatientModel pm;
    AppointmentModel am;

    // Get the id of the selected Patient
    QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    Patient selectedPatient = pm.getPatientFromCf(selectedPatientCf);

    Appointment newApp;
    newApp.id = associatedAppointment.id;
    newApp.fk_patient = selectedPatient.id;
    newApp.datetime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm");
    newApp.reason = ui->txtReason->toPlainText();
    newApp.fk_status = ui->cmbStatus->currentIndex();

    am.updateAppointment(newApp);

    close();
}


void EditAppointmentWindow::on_btnReminder_clicked()
{
    CredentialModel cm;
    PatientModel pm;

    // Get the selected Patient
    QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    Patient selectedPatient = pm.getPatientFromCf(selectedPatientCf);

    // SMTP address
    const QString smtp_address = cm.GetCredential("email_smtp_address");
    const int smtp_port = cm.GetCredential("email_smtp_port").toInt();

    // Sender data
    const QString sender_address = cm.GetCredential("email_username");
    const QString sender_name = "Dentiny";
    const QString sender_password = cm.GetCredential("email_password");

    // Receiver data
    const QString receiver_address = selectedPatient.email;
    const QString receiver_name = selectedPatient.name + " " + selectedPatient.surname;

    // Email data
    const QString SUBJECT = "Dentist appointment reminder!";
    const QString MESSAGE = "Don't forget your dentist appointment scheduled for " + associatedAppointment.datetime;

    //

    MimeMessage email;

    EmailAddress sender(sender_address, sender_name);
    EmailAddress receiver(receiver_address, receiver_name);

    email.setSender(sender);
    email.addRecipient(receiver);
    email.setSubject(SUBJECT);

    MimeText text;
    text.setText(MESSAGE);

    email.addPart(&text);

    // Now we can send the mail
    SmtpClient smtp(smtp_address, smtp_port, SmtpClient::SslConnection);

    smtp.connectToHost();

    if (!smtp.waitForReadyConnected())
    {
        qDebug() << "Failed to connect to host!";
    }

    smtp.login(sender_address, sender_password);

    if (!smtp.waitForAuthenticated())
    {
        qDebug() << "Failed to login!";
    }

    smtp.sendMail(email);

    if (!smtp.waitForMailSent())
    {
        qDebug() << "Failed to send mail!";
    }

    smtp.quit();
}

