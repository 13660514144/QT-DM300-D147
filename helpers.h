#ifndef HELPERS_H
#define HELPERS_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QThread>
#include <QTextCodec>
#include <qsettings.h>
#include <QCryptographicHash>
class HelperS
{
public:
    HelperS();

     QJsonObject buildjson(QString lastid,QString pagemothed);
     QString GetMd5(QString str);
     int GetTimespan();
     QJsonObject qstringtojson(QString str);
};

#endif // HELPERS_H
