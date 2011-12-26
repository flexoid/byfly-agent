#ifndef HTTP_H
#define HTTP_H

#include <QApplication>
#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QBuffer>

#include "settingsfile.h"
#include "controller.h"
#include "animimage.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFile;
class QHttp;
class QHttpResponseHeader;
class QSslError;
class QHttpRequestHeader;
class QUrl;
QT_END_NAMESPACE

class Http : public QObject
{
    Q_OBJECT

public:
    static Http* _self;
    static Http* instance()
    {
        if(!_self) _self = new Http();
        return _self;
    }
    void endSession();

protected:
    Http();

private slots:
    void httpRequestStarted(int requestId);
    void httpRequestFinished(int requestId, bool error);
    void readResponseHeader(const QHttpResponseHeader &responseHeader);
    void sslErrors(const QList<QSslError> &errors);
    void done();

public slots:
    void getBalance();
    void getStat();

private:
    bool busy;

    QHttp *http;
    QUrl url;

    int getBalanceId;
    int getStatId;

    QString login;
    QString password;
    QString chksum;

    void getSession(QString &data);
    void fillHeader(QHttpRequestHeader &requestHeader);

signals:
    void balansReceived(QString balans);
    void timeReceived(QString time);
    void trafficReceived(QString traffic);
    void incorrectSettings();
    void maxSessionsError();
    void incorrectLogin();
    void unknownError();

};

#endif // HTTP_H
