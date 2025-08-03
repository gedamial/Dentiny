#include "addpatientwindow.h"
#include "ui_addpatientwindow.h"
#include "model.h"
#include <QMessageBox>

AddPatientWindow::AddPatientWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddPatientWindow)
{
    ui->setupUi(this);

    Model m;

    // Pre-load birthplace combobox
    QList<Place> places = m.getAllPlaces();

    for(int i = 0; i< places.count(); ++i)
    {
        QString displayText = places[i].belfiore + " - " + places[i].name;
        if(!places[i].abbreviation.isEmpty())
        {
            displayText += " (" + places[i].abbreviation + ")";
        }

        ui->cmbBirthplace->addItem(displayText);
    }
}

AddPatientWindow::~AddPatientWindow()
{
    delete ui;
}

bool AddPatientWindow::InsertPatient()
{
    Model m;
    Patient toInsert;

    toInsert.cf = ui->txtFiscalCode->text();
    toInsert.name = ui->txtName->text();
    toInsert.surname = ui->txtSurname->text();
    toInsert.sex = ui->rbtnMale->isChecked() ? false : true;

    QString birthdayStr = ui->dateBirthday->date().toString("yyyy-MM-dd");

    toInsert.birthday = birthdayStr;

    QString belfiore = ui->cmbBirthplace->currentText().split("-")[0].trimmed();
    int fk_birthplace = m.getPlaceIdFromBelfiore(belfiore);

    if(fk_birthplace < 0)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("There was an error with the Birthplace value.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return false;
    }

    toInsert.fk_birthplace = fk_birthplace;
    toInsert.residence = ui->txtResidence->text();
    toInsert.email = ui->txtEmail->text();
    toInsert.phone = ui->txtPhone->text();

    return m.insertPatient(toInsert);
}

void AddPatientWindow::on_btnInsert_clicked()
{
    QMessageBox msgBox;

    if(ui->txtName->text().isEmpty())
    {
        msgBox.setInformativeText("Please insert a Name.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    else if(ui->txtSurname->text().isEmpty())
    {
        msgBox.setInformativeText("Please insert a Surname.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    else if(ui->txtResidence->text().isEmpty())
    {
        msgBox.setInformativeText("Please insert a Residence.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    else if(ui->txtEmail->text().isEmpty() || ui->txtPhone->text().isEmpty())
    {
        msgBox.setInformativeText("Please insert an email or a phone number.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    else
    {
        if(InsertPatient())
        {
            msgBox.setInformativeText("Patient added successfully.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();

            close();
        }
        else
        {
            msgBox.setInformativeText("A database error occurred while inserting new patient.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}


void AddPatientWindow::on_btnCancel_clicked()
{
    close();
}

