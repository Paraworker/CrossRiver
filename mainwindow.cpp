#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crossriver.h"
#include"introwindow.h"
#include"historywindow.h"
#include <vector>
#include <QString>
#include <QMessageBox>
#include<QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->btn_start,SIGNAL(clicked(bool)),this,SLOT(btn_start_clicked()));
    connect(this->ui->btn_clear,SIGNAL(clicked(bool)),this,SLOT(btn_clear_clicked()));
    this->ui->btn_clear->setDisabled(true);
    connect(this->ui->btn_ready,SIGNAL(clicked(bool)),this,SLOT(btn_ready_clicked()));
    this->ui->groupBox_choice->setHidden(true);
    connect(this->ui->btn_restart,SIGNAL(clicked(bool)),this,SLOT(btn_restart_clicked()));
    this->ui->btn_restart->setDisabled(true);
    this->ui->btn_history->setDisabled(true);
    connect(this->ui->btn_about,SIGNAL(clicked(bool)),this,SLOT(btn_about_clicked()));
    connect(this->ui->btn_history,SIGNAL(clicked(bool)),this,SLOT(btn_history_clicked()));
    move_0 = new QPropertyAnimation(this->ui->boat, "pos");     //从左往右移动动画
    move_0->setDuration(900);
    move_0->setStartValue(QPoint(200, 110));
    move_0->setEndValue(QPoint(420, 110));
    move_0->setEasingCurve(QEasingCurve::InOutQuad);
    move_1 = new QPropertyAnimation(this->ui->boat, "pos");     //从右往左移动动画
    move_1->setDuration(900);
    move_1->setStartValue(QPoint(420, 110));
    move_1->setEndValue(QPoint(200, 110));
    move_1->setEasingCurve(QEasingCurve::InOutQuad);
    choice=new std::vector<Cross>;
    timenow=new Time(3,3,0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete choice;
    delete timenow;
    delete move_0;
    delete move_1;
}

void MainWindow::btn_start_clicked()
{
    this->ui->listWidget->clear();
    std::vector<std::vector<Cross> > answer;
    solution(answer);
    int ways=(int)answer.size();
    for (int i=0;i<ways;i++)
    {
        this->ui->listWidget->addItem("第"+QString::number(i+1)+"种方案");
        std::vector<Cross>::iterator itr1,itr2;
        itr1=answer[(unsigned long)i].begin();
        itr2=answer[(unsigned long)i].end();
        for (;itr1!=itr2;itr1++)
        {
            QString a;
            if(itr1->boat_direction==0)
                a="划船到对岸";
            else
                a="划船回来";
            QString s=QString::number(itr1->goodman)+"个传教士与"+QString::number(itr1->wild)+"个野人  "+a;
            this->ui->listWidget->addItem(s);
        }
    }
   this->ui->btn_start->setDisabled(true);
   this->ui->btn_start->setText("过河结束");
   this->ui->btn_clear->setEnabled(true);
}

void MainWindow::btn_clear_clicked()
{
    this->ui->listWidget->clear();
    this->ui->btn_clear->setDisabled(true);
    this->ui->btn_start->setEnabled(true);
    this->ui->btn_start->setText("开始过河");
}

void MainWindow::btn_ready_clicked()
{
    this->ui->btn_ready->setHidden(true);
    this->ui->lable_welcome->setHidden(true);
    this->ui->groupBox_choice->setVisible(true);
    aboard(timenow->bank_left,0,*choice);
    for (int i=0;(unsigned long)i<choice->size();i++)
    {
        QString s=QString::number((*choice)[(unsigned long)i].goodman)+"个传教士与"+QString::number((*choice)[(unsigned long)i].wild)+"个野人  "+"划船到对岸";
        this->ui->listWidget_choice->addItem(s);
    }
    left_good.push_back(this->ui->label_left_goodman);
    left_good.push_back(this->ui->label_left_goodman_2);
    left_good.push_back(this->ui->label_left_goodman_3);
    left_wild.push_back(this->ui->label_left_wild);
    left_wild.push_back(this->ui->label_left_wild_2);
    left_wild.push_back(this->ui->label_left_wild_3);
    right_good.push_back(this->ui->label_right_goodman);
    right_good.push_back(this->ui->label_right_goodman_2);
    right_good.push_back(this->ui->label_right_goodman_3);
    right_wild.push_back(this->ui->label_right_wild);
    right_wild.push_back(this->ui->label_right_wild_2);
    right_wild.push_back(this->ui->label_right_wild_3);
    for (unsigned long i=0;i<3;i++) {
        right_good[i]->setHidden(true);
        right_wild[i]->setHidden(true);
    }
}

void MainWindow::choice_selected(int a)
{
    if((*choice)[(unsigned long)a].boat_direction==0)
    {
    timenow->bank_left.goodman=timenow->bank_left.goodman-(*choice)[(unsigned long)a].goodman;
    timenow->bank_left.wild= timenow->bank_left.wild - (*choice)[(unsigned long)a].wild;
    timenow->bank_right.goodman=timenow->bank_right.goodman+(*choice)[(unsigned long)a].goodman;
    timenow->bank_right.wild= timenow->bank_right.wild + (*choice)[(unsigned long)a].wild;
    timenow->boat=1;

    move_0->start();
    }
    else
    {
        timenow->bank_left.goodman=timenow->bank_left.goodman+(*choice)[(unsigned long)a].goodman;
        timenow->bank_left.wild= timenow->bank_left.wild + (*choice)[(unsigned long)a].wild;
        timenow->bank_right.goodman=timenow->bank_right.goodman-(*choice)[(unsigned long)a].goodman;
        timenow->bank_right.wild= timenow->bank_right.wild - (*choice)[(unsigned long)a].wild;
        timenow->boat=0;
        move_1->start();
    }
    for (unsigned long i=0;i<3;i++) {
        left_good[i]->setHidden(true);
        left_wild[i]->setHidden(true);
        right_good[i]->setHidden(true);
        right_wild[i]->setHidden(true);
    }
    for (int i=0;i<timenow->bank_left.goodman;i++) {
        left_good[(unsigned long)i]->setVisible(true);
    }
    for (int i=0;i<timenow->bank_left.wild;i++) {
        left_wild[(unsigned long)i]->setVisible(true);
    }
    for (int i=0;i<timenow->bank_right.goodman;i++) {
        right_good[(unsigned long)i]->setVisible(true);
    }
    for (int i=0;i<timenow->bank_right.wild;i++) {
        right_wild[(unsigned long)i]->setVisible(true);
    }
    if(timenow->bank_left.goodman==0&&timenow->bank_left.wild==0)
    {
        QMessageBox::information(nullptr, "过河成功", "传教士和野人都已经到达河对岸");
        this->ui->listWidget_choice->setDisabled(true);
    }
    else if ((timenow->bank_left.goodman>=timenow->bank_left.wild||timenow->bank_left.goodman==0)&&(timenow->bank_right.goodman>=timenow->bank_right.wild||timenow->bank_right.goodman==0))
    {
       this->ui->listWidget_choice->clear();
        choice->clear();
        QString d;
        if(timenow->boat==0)
        {
            aboard(timenow->bank_left,timenow->boat,*choice);
            d="划船到对岸";
        }
        else
        {
            aboard(timenow->bank_right,timenow->boat,*choice);
            d="划船回来";
        }
        unsigned long count=choice->size();
        for (unsigned long i=0;i<count;i++) {
            QString s=QString::number((*choice)[i].goodman)+"个传教士与"+QString::number((*choice)[i].wild)+"个野人  "+d;
            this->ui->listWidget_choice->addItem(s);
        }
    }
    else
    {
        QMessageBox::information(nullptr, "过河失败", "有传教士被吃了");
        this->ui->listWidget_choice->setDisabled(true);
    }
}

    void MainWindow::btn_restart_clicked()
    {
        this->ui->btn_restart->setDisabled(true);
        this->ui->btn_history->setDisabled(true);
        this->ui->listWidget_choice->setEnabled(true);
        this->history.clear();
        delete choice;
        delete timenow;
        choice=new std::vector<Cross>;
        timenow=new Time(3,3,0,0,0);
        this->ui->listWidget_choice->clear();
        aboard(timenow->bank_left,0,*choice);
        for (unsigned long i=0;i<choice->size();i++) {
            QString s=QString::number((*choice)[i].goodman)+"个传教士与"+QString::number((*choice)[i].wild)+"个野人  "+"划船到对岸";
            this->ui->listWidget_choice->addItem(s);
        }
        for (unsigned long i=0;i<3;i++) {
            left_good[i]->setVisible(true);
            left_wild[i]->setVisible(true);
            right_good[i]->setHidden(true);
            right_wild[i]->setHidden(true);
        }
        move_0->stop();
        move_1->stop();
        this->ui->boat->setGeometry(200,110,65,60);
    }

void MainWindow::on_listWidget_choice_clicked(const QModelIndex &index)
{
    this->ui->btn_restart->setEnabled(true);
    this->ui->btn_history->setEnabled(true);
    int cur=this->ui->listWidget_choice->currentRow();
    QString s=this->ui->listWidget_choice->item(cur)->text();
    this->history.push_back(s);
    choice_selected(cur);
}

void MainWindow::btn_about_clicked()
{
    IntroWindow i;
    i.exec();
}

void MainWindow::btn_history_clicked()
{
    historywindow h;
    h.add(history);
    h.exec();
}

