#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    mainwin=new MainWindow(0);
    mainwin->show();
    this->close();
}

void Login::on_pushButton_clicked()
{
    QApplication* app;
    app->exit(0);
}
