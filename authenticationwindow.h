#ifndef AUTHENTICATIONWINDOW_H
#define AUTHENTICATIONWINDOW_H

#include <QDialog>

enum class AuthenticationResult
{
    Aborted,
    Failed,
    Success
};

namespace Ui {
class AuthenticationWindow;
}

class AuthenticationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticationWindow(QWidget *parent = nullptr);
    ~AuthenticationWindow();

    AuthenticationResult getAuthenticationResult();

private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

private:
    Ui::AuthenticationWindow *ui;

    AuthenticationResult AuthResult;
};

#endif // AUTHENTICATIONWINDOW_H
