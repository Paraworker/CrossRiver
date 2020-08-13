#ifndef WAYSWINDOW_H
#define WAYSWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class wayswindow;
}

class wayswindow : public QDialog
{
    Q_OBJECT

public:
    explicit wayswindow(QWidget *parent = nullptr);
    void add(QString s);
    ~wayswindow();

private:
    Ui::wayswindow *ui;
};

#endif // WAYSWINDOW_H
