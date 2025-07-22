#ifndef ADDPATIENTWINDOW_H
#define ADDPATIENTWINDOW_H

#include <QDialog>

namespace Ui {
class AddPatientWindow;
}

class AddPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientWindow(QWidget *parent = nullptr);
    ~AddPatientWindow();

private slots:
    void on_btnInsert_clicked();
    void on_btnCancel_clicked();

private:
    Ui::AddPatientWindow *ui;

    bool InsertPatient();
};

#endif // ADDPATIENTWINDOW_H
