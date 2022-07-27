#ifndef QMESSAGE_H
#define QMESSAGE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMessageBox>
class qmessage
{
public:
    qmessage();
    void QMsginfo(QString txttitle,QString txtmsg);
    void QMsg(QString txtmsg);
    int QMsgOkCancel(QString txttitle,QString txtmsg);
    void QmsgErr(int err);
};

#endif // QMESSAGE_H
