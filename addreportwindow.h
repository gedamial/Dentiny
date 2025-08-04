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
    void on_btnUpload_clicked();

    void on_btnOK_clicked();

private:
    Ui::AddReportWindow *ui;

    QStringList uploadedFilePaths;
};

#endif // ADDREPORTWINDOW_H
