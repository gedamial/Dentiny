#ifndef ADDAPPOINTMENTWINDOW_H
#define ADDAPPOINTMENTWINDOW_H

#include <QDialog>

namespace Ui {
class AddAppointmentWindow;
}

class AddAppointmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddAppointmentWindow(const QDate defaultDate, QWidget *parent = nullptr);
    ~AddAppointmentWindow();

private slots:
    void on_btnCancel_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::AddAppointmentWindow *ui;
};

#endif // ADDAPPOINTMENTWINDOW_H
