#include "historywindow.h"
#include "ui_historywindow.h"
#include<vector>
#include<QString>

historywindow::historywindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::historywindow)
{
    ui->setupUi(this);
}

historywindow::~historywindow()
{
    delete ui;
}

void historywindow::add(std::vector<QString> &history)
{
    std::vector<QString>::iterator itr1,itr2;
    itr1=history.begin();
    itr2=history.end();
    for (;itr1!=itr2;itr1++)
    {
        this->ui->listWidget_history->addItem(*itr1);
    }
}
