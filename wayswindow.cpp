#include "wayswindow.h"
#include "ui_wayswindow.h"
#include <QString>

wayswindow::wayswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wayswindow)
{
    ui->setupUi(this);
}

void wayswindow::add(QString s)
{
    this->ui->listWidget_ways->addItem(s);
}

wayswindow::~wayswindow()
{
    delete ui;
}
