#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"crossriver.h"
#include<QPushButton>
#include<QString>
#include<QPropertyAnimation>
#include<QLabel>
#include<vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void btn_start_clicked();
    void btn_clear_clicked();
    void btn_ready_clicked();
    void btn_restart_clicked();
    void on_listWidget_choice_clicked(const QModelIndex &index);
    void btn_about_clicked();
    void btn_history_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<Cross> > *answer;
    std::vector<Cross>* choice;
    Time* timenow;      //当前状态 用于娱乐模式
    std::vector<QString> history;       //储存历史记录 用于娱乐模式
    void choice_selected(int a);
    QPropertyAnimation *move_0;
    QPropertyAnimation *move_1;
    std::vector<QLabel*> left_good;     //用于操作传教士和野人图标显示和隐藏的QLabel指针数组
    std::vector<QLabel*> left_wild;
    std::vector<QLabel*> right_good;
    std::vector<QLabel*> right_wild;
};
#endif // MAINWINDOW_H
