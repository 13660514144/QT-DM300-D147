#ifndef SQLITEUTIL_H
#define SQLITEUTIL_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QList>
#include <QVariant>
#include <QSqlQueryModel>
class sqliteutil : public QObject
{
    Q_OBJECT
public:
    explicit sqliteutil(const QString& strDatabase = "smart.db");
    //explicit sqliteutil(QObject *parent = 0);
    ~sqliteutil();
    bool createConnection(const QString& strConn);

        QSqlRecord ExecuteRecord(const QString& strQuery);
        QSqlRecord ExecuteRecord(const QString& strQuery, QList<QVariant> lstParameter);
        QSqlRecord ExecuteRecord(const QString& strQuery, QVariant Parameter);

        QSqlQuery ExecuteSqlQuery(const QString& strQuery, QList<QVariant> lstParameter);
        QSqlQuery ExecuteSqlQuery(const QString& strQuery, QVariant Parameter);
        QSqlQuery ExecuteSqlQuery(const QString& strQuery);

        int ExecuteInt(const QString& strQuery);
        int ExecuteInt(const QString& strQuery, QList<QVariant> lstParameter);
        int ExecuteInt(const QString& strQuery, QVariant Parameter);

        bool Execute(const QString& strQuery, QVariant Parameter);
        bool Execute(const QString& strQuery, QList<QVariant> lstParameter);

        QString ExecuteString(const QString& strQuery);

        void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery);
        void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                               QList<QVariant> lstParameter);
        void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery, QVariant Parameter);
private:
    QSqlDatabase m_db;
    QString m_strDatabase;
signals:

public slots:
};

#endif // SQLITEUTIL_H
