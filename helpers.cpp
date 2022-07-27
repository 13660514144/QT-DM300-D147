#include "helpers.h"

HelperS::HelperS()
{

}

QJsonObject HelperS::buildjson(QString lastid, QString pagemothed)
{
    QJsonObject jsonObject;
    QJsonArray pointAry;
    jsonObject.insert("IdCode","62412c5f83e3ebef97021241");
    jsonObject.insert("Role","");
    jsonObject.insert("DelFlg",1);
    jsonObject.insert("GroupFlg","");
    jsonObject.insert("LastId",lastid);
    jsonObject.insert("PageNextOrPre",pagemothed);
    jsonObject.insert("WhereCollection",pointAry);
    jsonObject.insert("rows",20);
    jsonObject.insert("pages",20);
    return jsonObject;
}


QString HelperS::GetMd5(QString str)
{
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash ( str.toLatin1(), QCryptographicHash::Md5 );
    md5.append(bb.toHex());
    return md5;
}

int HelperS::GetTimespan()
{
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();   //将当前时间转为时间戳
    return timeT;
}

QJsonObject HelperS::qstringtojson(QString str)
{

}
