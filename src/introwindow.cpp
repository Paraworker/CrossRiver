#include "introwindow.h"
#include "ui_introwindow.h"
#include"crossriver.h"

IntroWindow::IntroWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroWindow)
{
    ui->setupUi(this);
    this->ui->textBrowser->setPlainText(about());
    this->ui->label_website->setText("<a style='color: #2952A0;' href=\"https://github.com/Paraworker/CrossRiver\">网站");
    this->ui->label_licenses->setText("<a style='color: #2952A0;' href=\"https://www.gnu.org/licenses/gpl-3.0.html\">GNU 通用公共许可证 v3.0");
}

IntroWindow::~IntroWindow()
{
    delete ui;
}
