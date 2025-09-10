#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appointmentobserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public AppointmentObserver
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnNewPatient_clicked();

    void on_calendarWidget_selectionChanged();

    void on_btnNewAppointment_clicked();

    void UpdateAppointmentsList();

    void on_btnAddNewRecord_clicked();

    void on_btnSetPassword_clicked();

    void on_actionExit_triggered();

    void on_actionPatient_triggered();

    void on_actionReports_triggered();

private:
    Ui::MainWindow *ui;

    virtual void UpdateAppointments() override;
};


#endif // MAINWINDOW_H
