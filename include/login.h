#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "../include/mainwindow.h"

namespace Ui {
class login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void setMainWindow(MainWindow *main);

private slots:
    void on_submit_clicked();

private:
    Ui::login *ui;
    MainWindow *main;
};

#endif // LOGIN_H
