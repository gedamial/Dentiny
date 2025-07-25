#include "appointmentitem.h"
#include "ui_appointmentitem.h"

#include "editappointmentwindow.h"

AppointmentItem::AppointmentItem(int ID, QWidget *parent) : QWidget(parent), ui(new Ui::AppointmentItem), ID{ID}
{
    ui->setupUi(this);
}

int AppointmentItem::getID()
{
    return ID;
}

void AppointmentItem::mousePressEvent(QMouseEvent *event)
{
    if(ID < 0)
        return;

    EditAppointmentWindow wndw(ID);
    wndw.exec();
}

AppointmentItem::~AppointmentItem()
{
    delete ui;
}
