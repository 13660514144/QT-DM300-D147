#include "qmessage.h"

qmessage::qmessage()
{

}

void qmessage::QMsginfo(QString txttitle, QString txtmsg)
{
    QMessageBox msgBox;
    msgBox.setText(txttitle);
    msgBox.setInformativeText(txtmsg);
    int ret = msgBox.exec();

}
void qmessage::QmsgErr(int err)
{
    QMessageBox msgBox;
    switch (err) {
    case 0:
        msgBox.setText("操作成功");
        break;
    case -1:
        msgBox.setText("索引越界或没有找到合适的索引值");
        break;
    case -2:
        msgBox.setText("提供的Buffer长度数据错误");
        break;
    case -3:
        msgBox.setText("无效句柄");
        break;
    case -4:
        msgBox.setText("无效地址");
        break;
    case -5:
        msgBox.setText("无效数据");
        break;
    case -6:
        msgBox.setText("申请内存失败");
        break;
    case -7:
        msgBox.setText("不提供该支持");
        break;
    case -8:
        msgBox.setText("数据编码错误");
        break;
    case -9:
        msgBox.setText("数据错误");
        break;
    case -10:
        msgBox.setText("数据太长");
        break;
    case -11:
        msgBox.setText("没有数据");
        break;
    case -12:
        msgBox.setText("参数错误");
        break;
    case -13:
        msgBox.setText("超时");
        break;
    case -14:
        msgBox.setText("设备命令已经存在");
        break;
    case -15:
        msgBox.setText("USB或串口未连接");
        break;
    case -16:
        msgBox.setText("非接卡操作错误");
        break;
    case -17:
        msgBox.setText("PSAM卡操作错误");
        break;
    default:
        msgBox.setText("不知道什么错误，哈哈哈!!!");
        break;
    }
    msgBox.exec();
}
void qmessage::QMsg(QString txtmsg)
{
    QMessageBox msgBox;
    msgBox.setText(txtmsg);
    msgBox.exec();
}

int qmessage::QMsgOkCancel(QString txttitle, QString txtmsg)
{
    QMessageBox msgBox;
    int flg;
    msgBox.setText(txttitle);
    msgBox.setInformativeText(txtmsg);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Ok:
          flg=0;
          break;
      case QMessageBox::Cancel:
          flg=1;
          break;
      default:
          flg=0;
          break;
    }
    return flg;
}
