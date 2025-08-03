#ifndef SETPASSWORDWINDOW_H
#define SETPASSWORDWINDOW_H

#include <QDialog>

namespace Ui {
class SetPasswordWindow;
}

class SetPasswordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetPasswordWindow(QWidget *parent = nullptr);
    ~SetPasswordWindow();

    int exec() override;

private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

private:
    Ui::SetPasswordWindow *ui;
};

#endif // SETPASSWORDWINDOW_H
