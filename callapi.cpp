
#include "callapi.h"

callapi::callapi()
{
    qmsg=new qmessage;
}

QJsonObject callapi::sendGetRequest(QString httpurl)
{
    QJsonObject Qjsonobject;
    QString URL;
    QString ContentType;
    try
    {
        QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();

            //设置url
            QString url =httpurl;
            QNetworkRequest requestInfo;
            requestInfo.setUrl(QUrl(url));

            //添加事件循环机制，返回后再运行后面的
            QEventLoop eventLoop;
            QNetworkReply *reply =  m_pHttpMgr->get(requestInfo);
            QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
            eventLoop.exec();       //block until finish

            //错误处理
            if (reply->error() != QNetworkReply::NoError)
            {
                qDebug()<<"request protobufHttp handle errors here";
                QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
                qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
                qDebug(qPrintable(reply->errorString()));
            }

            //请求返回的结果
            QByteArray responseByte = reply->readAll();

            QString strRes = responseByte;
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseByte);
            QJsonObject Qjsonobject= jsonDocument.object();
    }
    catch (std::exception& ex)
    {
        qmsg->QMsginfo("sendGetRequest",ex.what());
    }
    return Qjsonobject;
}

QJsonObject callapi::sendPostRequest(QString httpurl, QJsonObject jsonpara,QString ContentType)
{
    QJsonObject Qjsonobject;

    try
    {
        QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
        //设置url
        QString url = httpurl;
        //设置头信息
        QNetworkRequest requestInfo;
        requestInfo.setUrl(QUrl(url));
        requestInfo.setHeader(QNetworkRequest::ContentTypeHeader,QVariant(ContentType));
        //requestInfo.setRawHeader("Content-Type","application/json");//服务器要求的数据头部
        //requestInfo.setRawHeader("Accept","text/json,*/*;q=0.5");//服务器要求的数据头部


        QJsonDocument jsonDoc;
        jsonDoc.setObject(jsonpara);
        QByteArray qByteHttpData = jsonDoc.toJson();
        QNetworkReply *reply =  m_pHttpMgr->post(requestInfo, qByteHttpData);

        //添加事件循环机制，返回后再运行后面的
        QEventLoop eventLoop;
        QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
        eventLoop.exec();       //block until finish

        //错误处理
        if (reply->error() != QNetworkReply::NoError)
        {
            qDebug()<<"request protobufHttp handle errors here";
            QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
            qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
            qDebug(qPrintable(reply->errorString()));
        }

        //请求收到的结果
        QByteArray responseByte = reply->readAll();
        QString strRes = responseByte;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseByte);
        Qjsonobject= jsonDocument.object();
    }
    catch (std::exception& ex)
    {
        qmsg->QMsginfo("sendPostRequest",ex.what());
    }
    return Qjsonobject;
}
