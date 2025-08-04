#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
