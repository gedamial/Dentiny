#include "appointmentitem.h"
#include "ui_appointmentitem.h"

AppointmentItem::AppointmentItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentItem)
{
    ui->setupUi(this);
}

AppointmentItem::~AppointmentItem()
{
    delete ui;
}
