#ifndef EDITAPPOINTMENTWINDOW_H
#define EDITAPPOINTMENTWINDOW_H

#include <QDialog>
#include "appointment.h"

namespace Ui {
class EditAppointmentWindow;
}

class EditAppointmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditAppointmentWindow(unsigned int appointmentID, QWidget *parent = nullptr);
    ~EditAppointmentWindow();

private slots:
    void on_btnCancel_clicked();

    void on_btnSave_clicked();

    void on_btnReminder_clicked();

private:
    Ui::EditAppointmentWindow *ui;

    unsigned int appointmentID;
    Appointment associatedAppointment;
};

#endif // EDITAPPOINTMENTWINDOW_H
