#include "controller.h"

Controller* Controller::_self = 0;

Controller::Controller()
{
    scene = Scene::instance();
    timer = new QTimer(this);
    timer->start(SettingsFile::getUpdateInterval() * 60 * 1000);
}

void Controller::writeLog(int level, QString text)
{
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss <<->> ");
    if (level == Notice)
        out << "Notice: ";
    else if (level == Warning)
        out << "Warning: ";
    else if (level == Error)
        out << "Error: ";
    else if (level == Critical)
        out << "Critical: ";
    out << text << "\r\n";
    file.close();
}

void Controller::updateBalance(QString balance)
{
    QString color;
    color = "d76b00";
    balance.replace(QRegExp("\\..+"), "");
    if (scene->balanceText)
        scene->balanceText->setHtml(QString("<font color=blue>" + tr("Balance:") + " </font><font color=#%2>" + tr("%1 b.r.") + "</font>").arg(balance, color));
}

void Controller::updateTime(QString time)
{
    if (scene->timeText)
        scene->timeText->setHtml(QString("<font color=blue>" + tr("Time:") + " </font><font color=#d76b00>" + tr("%1") + "</font>").arg(time));
}

void Controller::updateTraffic(QString traffic)
{
     if (scene->trafficText)
        scene->trafficText->setHtml(QString("<font color=blue>" + tr("Traffic:") + " </font><font color=#d76b00>" + tr("%1 Mb") + "</font>").arg(traffic));
}

void Controller::incorrectSettings()
{
    QMessageBox::information(0, qApp->applicationName() + tr(" - Error"), tr("Can not to get information\n") + tr("Login or password not found"));
}

void Controller::maxSessionsError()
{
    QMessageBox::information(0, qApp->applicationName() + tr(" - Error"), tr("Can not to get information\n") + tr("Max sessions exceeded"));
}

void Controller::incorrectLogin()
{
    QMessageBox::information(0, qApp->applicationName() + tr(" - Error"), tr("Can not to get information\n") + tr("Incorrect login or password"));
}

void Controller::unknownError()
{
    QMessageBox::information(0, qApp->applicationName() + tr(" - Error"), tr("Can not to get information\n") + tr("Unknown error"));
}

void Controller::updateSettings()
{
    timer->setInterval(SettingsFile::getUpdateInterval() * 60 * 1000);
}

void Controller::openSettingsWidget()
{
    SettingsDialog *settingsDialog = new SettingsDialog();
    connect(settingsDialog, SIGNAL(settingsApplied()),
            View::instance(), SLOT(updateSettings()));
    connect(settingsDialog, SIGNAL(settingsApplied()),
            Controller::instance(), SLOT(updateSettings()));
    connect(settingsDialog, SIGNAL(okClickedSignal()),
            Http::instance(), SLOT(getBalance()));
}

void Controller::about()
{
    QMessageBox::about(0, tr("About"), "<div align=center><b>Made by <font color=red>FlexoID</font></b><br /><b>E-mail, Jabber:</b> <a href=mailto:flexoid@gmail.com>FlexoID@gmail.com</a><br /><b>icq:</b> 767-34-64</div>");
}

void Controller::quit()
{
    Http::instance()->endSession();
    SettingsFile::setValue("Data/StartPos", View::instance()->pos());
    qApp->quit();
}
