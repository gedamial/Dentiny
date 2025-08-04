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
        QMessageBox::critical(this, "Invalid Birthplace value", "There was an error with the Birthplace value.", QMessageBox::Ok);
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

    else if(ui->txtEmail->text().isEmpty() || ui->txtPhone->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid email or phone number", "Please insert an email or phone number.", QMessageBox::Ok);
    }

    else
    {
        if(InsertPatient())
        {
            QMessageBox::information(this, "Patient added", "Patient added successfully!", QMessageBox::Ok);
            close();
        }

        else
        {
            QMessageBox::critical(this, "Database error", "A database error occurred while inserting new patient.", QMessageBox::Ok);
        }
    }
}

void AddPatientWindow::on_btnCancel_clicked()
{
    close();
}
