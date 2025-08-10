#include "reportitem.h"
#include "ui_reportitem.h"

ReportItem::ReportItem(QWidget *parent) : QWidget(parent), ui(new Ui::ReportItem)
{
    ui->setupUi(this);

    ui->btnApply->setEnabled(false);
}

ReportItem::~ReportItem()
{
    delete ui;
}

void ReportItem::on_txtNotes_textChanged()
{
    ui->btnApply->setEnabled(true);
}

