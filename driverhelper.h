#ifndef DRIVERHELPER_H
#define DRIVERHELPER_H
#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include "ICReader.h"
#include "qmessage.h"
class driverhelper:public QObject
{
     Q_OBJECT
public:
    explicit driverhelper(QObject *parent = 0);
    ~driverhelper();
    bool Isconnect();
    bool cardtureflg(std::string str);
    bool trackflg(std::string str);
    void readcodechange(unsigned char data[]);
    void readcodechange147(unsigned char data[]);
    std::string DecIntToHexStr(long long num);
    char* _10_to_16(long long a);
signals:
    void signCardMsg(QString message); // 接受到readcodechange类型消息的信号

private:
    bool _connectd;
private :
    qmessage *qmsg;

};

#endif // DRIVERHELPER_H
