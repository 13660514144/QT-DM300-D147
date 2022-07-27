#include "driverhelper.h"
driverhelper::driverhelper(QObject *parent)
    : QObject(parent)
{
    _connectd=false;
    qmsg=new qmessage;
}

driverhelper::~driverhelper()
{

}
bool driverhelper::Isconnect()
{
    try
    {
        if (!_connectd)
        {
            int s = USBHidInitCommunicate();
            if (s != 0)
            {
                _connectd = false;
                //qmsg->QMsginfo("connect","设备连接失败");
            }
            else
            {
                _connectd = true;
                //qmsg->QMsginfo("connect","设备连接成功");
            }
            qmsg->QmsgErr(s);
        }
    }
    catch (std::exception& ex)
    {
        _connectd=false;
        qmsg->QMsginfo("Isconnect",ex.what());
    }
    return _connectd;
}
bool driverhelper::trackflg(std::string str)
{
    bool bIsDigit = true;
    try
    {
        int strvalue=atoi(str.c_str());
        if(strvalue>62)
        {
            qmsg->QMsg("超出区块范围，请重新定义");
            return false;
        }
        bIsDigit=(strvalue==0) ? false:true;
        if(bIsDigit==true)
        {
            for(int x=0;x<16;x++)
            {
                if(strvalue==(x*4+3))
                {
                    bIsDigit=false;
                    qmsg->QMsg("非法起始区块，请重新定义");
                    break;
                }
            }
        }
        else
        {
           qmsg->QMsg("0区块禁止写入，请重新定义");
        }
    }
    catch(std::exception& ex)
    {
        bIsDigit=false;
        qmsg->QMsg(ex.what());
    }
    return bIsDigit;
}
bool driverhelper::cardtureflg(std::string str)
{
    bool bIsDigit = true;
    try
    {
        long long  strvalue= strtoll(str.c_str(), NULL, 10);//atoi(str.c_str());
        if(strvalue==0 || strvalue>4294967295)
        {
            qmsg->QMsg("非法数字");
            return false;
        }
        //int strvalue=atoi(str.c_str());
        int nCount = str.length(); // 获得字符个数
        for(int i=0;i<nCount;i++)
        {
            int tmp = (int)str[i];
            if (tmp >= 48 && tmp <= 57)
            {
                continue;
            }
            else
            {
                qmsg->QMsg("非法数字");
                return false;
            }
        }
    }
    catch (std::exception& ex)
    {
        bIsDigit=false;
        qmsg->QMsg(ex.what());
    }
    return bIsDigit;
}

void driverhelper::readcodechange(unsigned char data[])
{    
    std::string str = "";
    try
    {
        long num1 = data[0];
        long num2 = data[1];
        long num3 = data[2];
        std::string cardcode = std::to_string(num1);

        //ui->msgline->setText(QString::fromStdString(to_string(num1)) + "\r\n") ;

        std::string tmpcode = DecIntToHexStr(num2);
        tmpcode += DecIntToHexStr(num3);
        const char* head = tmpcode.c_str();
        int num4 = 0;
        sscanf(head, "%x", &num4);
        //ui->msgline->setText(QString::fromStdString(to_string(num4))+ "\r\n");

        cardcode += std::to_string(num4);
        str = cardcode;
        emit signCardMsg(QString::fromStdString(str));//通过信号槽传递参数
    }
    catch (std::exception& ex)
    {
        str = "";
        qmsg->QMsg(ex.what());
    }
}
//读卡转换
void driverhelper::readcodechange147(unsigned char data[])
{
    std::string str = "";
    try
    {
        long num1 = data[0];
        long num2 = data[1];
        long num3 = data[2];
        long num4 = data[3];
        //std::string cardcode = std::to_string(num1);

        //ui->msgline->setText(QString::fromStdString(to_string(num1)) + "\r\n") ;
        std::string tmp;
        tmp=DecIntToHexStr(num4);
        if(tmp.length()<2)
        {
            tmp="0"+tmp;
        }
        std::string tmpcode = tmp;
        tmp=DecIntToHexStr(num3);
        if(tmp.length()<2)
        {
            tmp="0"+tmp;
        }
        tmpcode += tmp;
        tmp=DecIntToHexStr(num2);
        if(tmp.length()<2)
        {
            tmp="0"+tmp;
        }
        tmpcode += tmp;
        tmp=DecIntToHexStr(num1);
        if(tmp.length()<2)
        {
            tmp="0"+tmp;
        }
        tmpcode += tmp;
        const char* head = tmpcode.c_str();
        unsigned int nummew = 0;
        sscanf(head, "%x", &nummew);
        //ui->msgline->setText(QString::fromStdString(to_string(num4))+ "\r\n");

        std::string  cardcode = std::to_string(nummew);
        str = cardcode;
        emit signCardMsg(QString::fromStdString(str));//通过信号槽传递参数
    }
    catch (std::exception& ex)
    {
        str = "";
        qmsg->QMsg(ex.what());
    }
}
std::string driverhelper::DecIntToHexStr(long long num)
{
    std::string str;
    long long Temp = num / 16;
    int left = num % 16;
    if (Temp > 0)
        str += DecIntToHexStr(Temp);
        if (left < 10)
            str += (left + '0');
        else
            str += ('A' + left - 10);
        return str;
}
char* driverhelper::_10_to_16(long long a){
    char* str = new char[10];
    int i = 0;
    long long temp = 0;
    while(a > 0){
        temp = a % 16;// 取余数
        str[i++] = temp >= 10 ? ((temp - 10) + 'a') : (temp + '0');
        a = a >> 4;
    }
    str[i] = '\0';
    // 翻转 , 将高位与地位进行翻转
    int t = 0;
    for(int j = 0; j < i / 2; j++){
        t = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = t;
    }
    return str;
}

