#ifndef REPORTITEM_H
#define REPORTITEM_H

#include <QWidget>

namespace Ui {
class ReportItem;
}

class ReportItem : public QWidget
{
    Q_OBJECT

public:
    explicit ReportItem(QWidget *parent = nullptr);
    ~ReportItem();

    Ui::ReportItem *ui;
private slots:
    void on_txtNotes_textChanged();
};

#endif // REPORTITEM_H
