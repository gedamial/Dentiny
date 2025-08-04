#ifndef VIEWPATIENTWINDOW_H
#define VIEWPATIENTWINDOW_H

#include <QDialog>

namespace Ui {
class ViewPatientWindow;
}

class ViewPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPatientWindow(QWidget *parent = nullptr);
    ~ViewPatientWindow();

private slots:
    void on_btnCancel_clicked();

    void on_cmbPatient_currentIndexChanged(int index);

    void on_chkboxEditMode_checkStateChanged(const Qt::CheckState& checkState);

    void SetFieldsEnabled(bool enabled);

    void on_btnOK_clicked();

private:
    Ui::ViewPatientWindow *ui;
};

#endif // VIEWPATIENTWINDOW_H
