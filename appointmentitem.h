#ifndef APPOINTMENTITEM_H
#define APPOINTMENTITEM_H

#include <QWidget>

namespace Ui {
class AppointmentItem;
}

class AppointmentItem : public QWidget
{
    Q_OBJECT

public:
    explicit AppointmentItem(QWidget *parent = nullptr);
    ~AppointmentItem();

    Ui::AppointmentItem *ui;
};

#endif // APPOINTMENTITEM_H
