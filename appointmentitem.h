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
    explicit AppointmentItem(int ID = -1, QWidget *parent = nullptr);
    ~AppointmentItem();

    Ui::AppointmentItem *ui;

    int getID();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    int ID;
};

#endif // APPOINTMENTITEM_H
