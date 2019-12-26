#include "introwindow.h"
#include "ui_introwindow.h"
#include"crossriver.h"

IntroWindow::IntroWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroWindow)
{
    ui->setupUi(this);
    this->ui->textBrowser->setPlainText(about());
}

IntroWindow::~IntroWindow()
{
    delete ui;
}
