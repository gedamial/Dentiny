#ifndef EDITPATIENTWINDOW_H
#define EDITPATIENTWINDOW_H

#include <QDialog>

namespace Ui {
class EditPatientWindow;
}

class EditPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditPatientWindow(QWidget *parent = nullptr);
    ~EditPatientWindow();

private slots:
    void on_btnCancel_clicked();

    void on_cmbPatient_currentIndexChanged(int index);

    void on_chkboxEditMode_checkStateChanged(const Qt::CheckState& checkState);

    void SetFieldsEnabled(bool enabled);

    void on_btnOK_clicked();

private:
    Ui::EditPatientWindow *ui;
};

#endif // EDITPATIENTWINDOW_H
