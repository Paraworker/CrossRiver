#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include <QDialog>

namespace Ui {
class IntroWindow;
}

class IntroWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IntroWindow(QWidget *parent = nullptr);
    ~IntroWindow();

private:
    Ui::IntroWindow *ui;
};

#endif // INTROWINDOW_H
