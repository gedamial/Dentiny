#include "editpatientwindow.h"
#include "ui_editpatientwindow.h"
#include "patientmodel.h"
#include "placemodel.h"
#include "patient.h"
#include <QMessageBox>

EditPatientWindow::EditPatientWindow(QWidget *parent) : QDialog(parent), ui(new Ui::EditPatientWindow)
{
    ui->setupUi(this);

    PatientModel pm;
    PlaceModel place_m;

    // Pre-load patient combobox
    QList<Patient> patients = pm.getAllPatientsSortedBySurname();

    for(int i = 0; i < patients.size(); ++i)
    {
        QString displayText = patients[i].surname + " " + patients[i].name + " - " + patients[i].cf;
        ui->cmbPatient->addItem(displayText);
    }

    // Pre-load birthplace combobox
    ui->cmbBirthplace->insertItem(0, "Select an option...");
    ui->cmbBirthplace->setItemData(0, false, Qt::ItemIsEnabled);

    QList<Place> places = place_m.getAllPlaces();

    for(int i = 0; i< places.count(); ++i)
    {
        QString displayText = places[i].belfiore + " - " + places[i].name;
        if(!places[i].abbreviation.isEmpty())
        {
            displayText += " (" + places[i].abbreviation + ")";
        }

        //ui->cmbBirthplace->addItem(displayText);
        ui->cmbBirthplace->insertItem(places[i].id, displayText);
    }

    ui->chkboxEditMode->setCheckable(false);
    SetFieldsEnabled(false);
}

EditPatientWindow::~EditPatientWindow()
{
    delete ui;
}

void EditPatientWindow::on_btnCancel_clicked()
{
    close();
}

void EditPatientWindow::on_cmbPatient_currentIndexChanged(int index)
{
    ui->chkboxEditMode->setCheckable(true);

    const QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();

    // Fill in the text fields with the selected patient information
    PatientModel pm;
    Patient selectedPatient = pm.getPatientFromCf(selectedPatientCf);

    ui->txtName->setText(selectedPatient.name);
    ui->txtSurname->setText(selectedPatient.surname);
    ui->txtFiscalCode->setText(selectedPatient.cf);
    ui->rbtnMale->setChecked(selectedPatient.sex == (int)PatientSex::Male);
    ui->rbtnFemale->setChecked(selectedPatient.sex == (int)PatientSex::Female);
    ui->dateBirthday->setDate(QDate::fromString(selectedPatient.birthday, "yyyy-MM-dd"));
    ui->cmbBirthplace->setCurrentIndex(selectedPatient.fk_birthplace);
    ui->txtResidence->setText(selectedPatient.residence);
    ui->txtEmail->setText(selectedPatient.email);
    ui->txtPhone->setText(selectedPatient.phone);
}

void EditPatientWindow::on_chkboxEditMode_checkStateChanged(const Qt::CheckState& checkState)
{
    if(checkState == Qt::CheckState::Checked)
    {
        SetFieldsEnabled(true);
    }

    else
    {
        SetFieldsEnabled(false);
    }
}

void EditPatientWindow::SetFieldsEnabled(bool enabled)
{
    ui->txtName->setReadOnly(!enabled);
    ui->txtSurname->setReadOnly(!enabled);
    ui->txtFiscalCode->setReadOnly(!enabled);
    //ui->rbtnMale->setEnabled(enabled);
    //ui->rbtnFemale->setEnabled(enabled);
    ui->dateBirthday->setEnabled(enabled);
    ui->cmbBirthplace->setEnabled(enabled);
    ui->txtResidence->setReadOnly(!enabled);
    ui->txtEmail->setReadOnly(!enabled);
    ui->txtPhone->setReadOnly(!enabled);
}

void EditPatientWindow::on_btnOK_clicked()
{
    if(ui->cmbPatient->currentIndex() < 0)
    {
        QMessageBox::warning(this, "Invalid patient", "Please select a patient.", QMessageBox::Ok);
        return;
    }

    PatientModel pm;
    const QString selectedPatientCf = ui->cmbPatient->currentText().split("-")[1].trimmed();
    Patient selectedPatient = pm.getPatientFromCf(selectedPatientCf);

    if(ui->txtName->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid name", "Please insert a Name.", QMessageBox::Ok);
    }

    else if(ui->txtSurname->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid surname", "Please insert a Surname.", QMessageBox::Ok);
    }

    else if(ui->dateBirthday->date() > QDate::currentDate())
    {
        QMessageBox::warning(this, "Invalid date", "Please insert a valid date.", QMessageBox::Ok);
    }

    else if(ui->txtResidence->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid residence", "Please insert a Residence.", QMessageBox::Ok);
    }

    else if(ui->txtEmail->text().isEmpty() && ui->txtPhone->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid email or phone number", "Please insert an email or phone number.", QMessageBox::Ok);
    }

    else
    {
        PlaceModel place_m;

        selectedPatient.name = ui->txtName->text();
        selectedPatient.surname = ui->txtSurname->text();
        selectedPatient.cf = ui->txtFiscalCode->text();
        selectedPatient.sex = ui->rbtnMale->isChecked() ? false : true;
        selectedPatient.birthday = ui->dateBirthday->date().toString("yyyy-MM-dd");

        QString belfiore = ui->cmbBirthplace->currentText().split("-")[0].trimmed();
        int fk_birthplace = place_m.getPlaceIdFromBelfiore(belfiore);

        if(fk_birthplace < 0)
        {
            QMessageBox::critical(this, "Invalid Birthplace value", "There was an error with the Birthplace value.", QMessageBox::Ok);
            return;
        }

        selectedPatient.fk_birthplace = fk_birthplace;
        selectedPatient.residence = ui->txtResidence->text();
        selectedPatient.email = ui->txtEmail->text();
        selectedPatient.phone = ui->txtPhone->text();

        if(pm.updatePatient(selectedPatient))
        {
            QMessageBox::information(this, "Patient updated", "Patient updated successfully!", QMessageBox::Ok);
            close();
        }

        else
        {
            QMessageBox::critical(this, "Database error", "A database error occurred while updating the patient.", QMessageBox::Ok);
        }
    }
}

