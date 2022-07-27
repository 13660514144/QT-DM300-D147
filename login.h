#ifndef LOGIN_H
#define LOGIN_H
#include "mainwindow.h"
#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_login_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    MainWindow *mainwin;
};

#endif // LOGIN_H
