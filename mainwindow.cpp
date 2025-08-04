#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addpatientwindow.h"
#include "appointment.h"
#include "appointmentitem.h"
#include "ui_appointmentitem.h"
#include "patient.h"
#include "addappointmentwindow.h"
#include "addreportwindow.h"
#include "setpasswordwindow.h"
#include "editpatientwindow.h"
#include "model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add header label before the list of Appointments
    AppointmentItem* lblAppointmentHeader = new AppointmentItem;
    ui->bottomLayout->insertWidget(0, lblAppointmentHeader);

    // Make sure the list appears on start-up
    UpdateAppointmentsList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnNewPatient_clicked()
{
    AddPatientWindow wndw;
    wndw.exec(); // automatically sets setModal to true
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    UpdateAppointmentsList();
}

void MainWindow::on_btnNewAppointment_clicked()
{
    AddAppointmentWindow wndw(ui->calendarWidget->selectedDate());
    wndw.exec(); // automatically sets setModal to true
}

void MainWindow::UpdateAppointmentsList()
{
    Model m;

    // Get appointments of the selected date
    QString selectedDate = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QList<Appointment> apps = m.getAppointmentsFromDateSorted(selectedDate);

    QWidget* container = new QWidget();                    // Container for the AppointmentItems
    QVBoxLayout* layout = new QVBoxLayout(container);      // Layout to stack them vertically
    layout->setAlignment(Qt::AlignTop);
    container->setLayout(layout);

    for(int i = 0; i < apps.size(); ++i)
    {
        AppointmentItem* appItem = new AppointmentItem(apps[i].id);
        Patient appPatient = m.getPatientFromId(apps[i].fk_patient);

        appItem->ui->lblHeader_Time->setText(apps[i].datetime.split(" ")[1]);
        appItem->ui->lblHeader_Name->setText(appPatient.name);
        appItem->ui->lblHeader_Surname->setText(appPatient.surname);
        appItem->ui->lblHeader_Reason->setText(apps[i].reason);
        appItem->ui->lblHeader_Status->setText(m.getStatusNameFromId(apps[i].fk_status));

        layout->addWidget(appItem);  // Add to the layout
    }

    ui->scrollArea->setWidget(container);
}

void MainWindow::on_btnAddNewRecord_clicked()
{
    AddReportWindow wndw;
    wndw.exec();
}

void MainWindow::on_btnSetPassword_clicked()
{
    SetPasswordWindow wndw;
    wndw.exec();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionPatient_triggered()
{
    EditPatientWindow wndw;
    wndw.exec();
}

