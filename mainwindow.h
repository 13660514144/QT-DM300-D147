#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "WebSocketClinet.h"
#include "helpers.h"
#include "callapi.h"
#include "driverhelper.h"
#include "qmessage.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QStringListModel *Model;
    QStandardItemModel *ItemModel;
    int pagenum=0;
    QString CurrentMothed="first";
    QString PageMothed="first";
    QString LastId="";
    QJsonObject pagejobject;
    QJsonArray pagejarray;
    void loadconfig();

private slots:
    void on_btnwrite_clicked();

    void on_btnread_clicked();

    void on_getgroup_clicked();
    void showClick(QModelIndex index);
    void on_buildview_clicked();
    void onTableClicked(QModelIndex index);
    void getlastid(QString bottid,QString topid);
private:
    Ui::MainWindow *ui;

private slots:
    void slotSendMsg(); // 发送消息的槽函数
    void slotRecvTextMsg(QString sMessage); // 接受WebSocketClient传来的文本消息
    void soltsetreadcode(QString code);
private:
    WebSocketClinet *m_pWebSocketClinet; // WebSocket客户端
    HelperS *help;
    callapi *api;
    driverhelper *drivers;
    qmessage *qmsg;
private:
    QTimer *fTimer; //定时器
    void inittimer();
    void stoptimer();
private slots:
    //void on_timer_timeout ();//定时溢出处理槽函数
    void on_btnpre_clicked();
    void on_btnnext_clicked();
signals:
    void buildtb_signal(QJsonObject json);
private slots:
    void buildtb_slots(QJsonObject json);
    void on_btnconfigread_clicked();
    void on_btnactive_clicked();
    void on_btpassive_clicked();
    void on_radioA_clicked();
    void on_radioB_clicked();
    void on_pushButton_clicked();
};


#endif // MAINWINDOW_H
