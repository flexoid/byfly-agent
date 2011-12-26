#include "http.h"
#include <QSettings>

Http* Http::_self = 0;

Http::Http()
{
    http = new QHttp;
    /*QList<QSslCipher> list;
    //for (int x = 21; x <= 23; x++)
    //    list.push_front(QSslSocket::supportedCiphers().at(x));
    QSslCipher ci1("EDH-RSA-DES-CBC-SHA", QSsl::SslV3);
    list.push_front(ci1);
    QSslSocket::setDefaultCiphers(list);
    */
    http->setHost("stat.byfly.by", QHttp::ConnectionModeHttps, 443);

    connect(http, SIGNAL(requestStarted(int)),
            this, SLOT(httpRequestStarted(int)));
    connect(http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));
    connect(http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),
            this, SLOT(readResponseHeader(const QHttpResponseHeader &)));
    connect(http, SIGNAL(sslErrors(const QList<QSslError> &)),
            this, SLOT(sslErrors(const QList<QSslError> &)));
    connect(http, SIGNAL(done(bool)),
            this, SLOT(done()));
    busy = false;
}

void Http::getBalance()
{
    if (busy)
        return;
    if (SettingsFile::getLogin() == "" || SettingsFile::getPassword() == "")
        return Controller::instance()->openSettingsWidget();

    AnimImage::instance()->show();

    url = "https://stat.byfly.by/KK_ABS_WEB_DB.callhpage";
    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    path.append("?p_logname=");
    path.append(SettingsFile::getLogin());
    path.append("&p_pwd=");
    path.append(SettingsFile::getPassword());

    QHttpRequestHeader header("GET", path);
    fillHeader(header);

    getBalanceId = http->request(header);
    busy = true;
}

void Http::getStat()
{
    url = "https://stat.byfly.by//KK_ABS_WEB.Show";
    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    path.append("?page_name=R-COUNTER");
    path.append("&logname=");
    path.append(login);
    path.append("&chksum=");
    path.append(chksum);

    QHttpRequestHeader header("GET", path);
    fillHeader(header);

    getStatId = http->request(header);
}

void Http::httpRequestStarted(int requestId)
{
}

void Http::httpRequestFinished(int requestId, bool error)
{
    if (error)
    {
        Controller::writeLog(Controller::Error, http->errorString());
        AnimImage::instance()->hide();
        busy = false;
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QString data(codec->toUnicode(http->readAll()));
    if (data.contains(QString("Ошибка!").toLocal8Bit()))
    {
        AnimImage::instance()->hide();
        busy = false;
        if (data.contains(QString("Превышено разрешенное количество одновременных сессий.").toLocal8Bit()))
        {
            maxSessionsError();
            Controller::writeLog(Controller::Error, "Max sessions error");
        }
        else if (data.contains(QString("Неверный логин или пароль!").toLocal8Bit()))
        {
            incorrectLogin();
            Controller::writeLog(Controller::Error, "Incorrect login or password");
        }
        else
            unknownError();
            Controller::writeLog(Controller::Error, "Unknown error");
        return;
    }
    if (requestId == getBalanceId)
    {
        QRegExp rx(QString::fromUtf8("<td width=\"50%\" class=\"ADM_HOME_DATA_DESC\">.*Текущее состояние лицевого счета.*<td width=\"50%\" class=\"ADM_HOME_DATA2\">.*([\\d.]+).*\\(BR\\)</td>"));
        rx.setMinimal(true);
        rx.setCaseSensitivity(Qt::CaseInsensitive);
        qDebug() << data;
        if (rx.indexIn(data) != -1)
        {
            balansReceived(rx.cap(1));
            getSession(data);
            getStat();
        }
        else
        {
            Controller::writeLog(Controller::Error, "Getting balance error");
            Controller::writeLog(Controller::Error, data);
            AnimImage::instance()->hide();
            busy = false;
        }
    }
    else if (requestId == getStatId)
    {
        QRegExp rx("<td class=\"ADM_REPORTS_BODY_INSIDE2\">radius_tm_all </td>\\n<td class=\"ADM_REPORTS_BODY_INSIDE2\">([\\d:]+) </td>");
        if (rx.indexIn(data) != -1)
        {
            timeReceived(rx.cap(1));
            rx.setPattern("<td class=\"ADM_REPORTS_BODY_INSIDE2\">radius_vl_all </td>\\n<td class=\"ADM_REPORTS_BODY_INSIDE2\">(\d+) Мб </td>");
            if (rx.indexIn(data) != -1)
            {
                trafficReceived(rx.cap(1));
            }
            else
            {
                rx.setPattern("radius_vl_in\\s.+INSIDE2\">([0-9]+)\\sМб\\s</TD><TD.+");
                if (rx.indexIn(data) != -1)
                {
                    QString trafic = rx.cap(1);
                    rx.setPattern("radius_vl_out\\s.+INSIDE2\">([0-9]+)\\sМб\\s</TD><TD");
                    if (rx.indexIn(data) != -1)
                    {
                        trafic += " / " + rx.cap(1);
                        trafficReceived(trafic);
                    }
                }
                else
                {
                    Controller::writeLog(Controller::Error, "Getting trafic error");
                    Controller::writeLog(Controller::Error, data);
                }
            }
        }
        else
        {
            Controller::writeLog(Controller::Error, "Getting time error");
            Controller::writeLog(Controller::Error, data);
        }
        endSession();
    }
}

void Http::readResponseHeader(const QHttpResponseHeader &responseHeader)
{
}

void Http::sslErrors(const QList<QSslError> &errors)
{
    foreach (const QSslError &error, errors)
        Controller::writeLog(Controller::Notice, error.errorString());
    http->ignoreSslErrors();
}

void Http::done()
{
}

void Http::getSession(QString &data)
{
    QRegExp rx("\'A-EXIT_PAGE\'\\,\\s\'(.+)\'\\,\\s\'(\\d+)\'\\);\"\\>Выход");
    if (rx.indexIn(data) != -1)
    {
        login = rx.cap(1);
        chksum = rx.cap(2);
    }
    else Controller::writeLog(Controller::Error, "Getting session error");
}

void Http::endSession()
{
    if (!chksum.isEmpty())
    {
        QUrl sessUrl("https://stat.byfly.by/KK_ABS_WEB.Show");
        QByteArray sessPath = QUrl::toPercentEncoding(sessUrl.path(), "!$&'()*+,;=:@/");

        sessPath.append("?page_name=A-EXIT_PAGE&logname=");
        sessPath.append(login);
        sessPath.append("&chksum=");
        sessPath.append(chksum);

        QHttpRequestHeader header("GET", sessPath);
        fillHeader(header);
        http->request(header);

        chksum = "";
    }
    AnimImage::instance()->hide();
    busy = false;
}

void Http::fillHeader(QHttpRequestHeader &requestHeader)
{
    requestHeader.setValue("Host", url.host());
    requestHeader.setValue("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru; rv:1.8.1.20) Gecko/20081217 Firefox/2.0.0.20 (.NET CLR 3.5.30729)");
    requestHeader.setValue("Accept", "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5");
    requestHeader.setValue("Connection", "close");
}
