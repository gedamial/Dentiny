#ifndef EDITREPORTSWINDOW_H
#define EDITREPORTSWINDOW_H

#include <QDialog>
#include "attachment.h"
#include "report.h"
#include "reportitem.h"
#include "observer.h"

namespace Ui {
class EditReportsWindow;
}

class EditReportsWindow : public QDialog, public Observer
{
    Q_OBJECT

public:
    explicit EditReportsWindow(QWidget *parent = nullptr);
    ~EditReportsWindow();

    int exec() override;

    void OpenAttachment(const Attachment& attachment);

private slots:
    void on_cmbPatient_currentIndexChanged(int index);

    void on_btnClose_clicked();

private:
    Ui::EditReportsWindow *ui;
    void SetupReportItem(ReportItem* reportItem, Report report);
    void RemoveReport(Report report);
    void UpdateReport(ReportItem* reportItem, Report report);

    void UpdateReportsList();

    virtual void UpdateReports() override;
};

#endif // EDITREPORTSWINDOW_H
