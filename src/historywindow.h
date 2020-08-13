#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QDialog>
#include<vector>
#include<QString>

namespace Ui {
class historywindow;
}

class historywindow : public QDialog
{
    Q_OBJECT

public:
    explicit historywindow(QWidget *parent = nullptr);
    ~historywindow();
    void add(std::vector<QString>& history);

private:
    Ui::historywindow *ui;
};

#endif // HISTORYWINDOW_H
