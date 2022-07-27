#ifndef CALLAPI_H
#define CALLAPI_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include "qmessage.h"
class callapi
{
public:
    callapi();
    QJsonObject sendGetRequest(QString httpurl);
    QJsonObject sendPostRequest(QString httpurl,QJsonObject jsonpara,QString ContentType);
private :
    qmessage *qmsg;
};

#endif // CALLAPI_H
