#ifndef ADDREPORTWINDOW_H
#define ADDREPORTWINDOW_H

#include <QDialog>

namespace Ui {
class AddReportWindow;
}

class AddReportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddReportWindow(QWidget *parent = nullptr);
    ~AddReportWindow();

    int exec() override;

private slots:
    void on_btnCancel_clicked();

private:
    Ui::AddReportWindow *ui;
};

#endif // ADDREPORTWINDOW_H
