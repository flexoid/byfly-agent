#include "settingsfile.h"

namespace SettingsFile
{

QString getLogin()
{
    QSettings *ini = new QSettings("./info.ini", QSettings::IniFormat);
    ini->deleteLater();
    return ini->value("Account/Login", "").toString();
}
void setLogin(QString login)
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    ini->setValue("Account/Login", login);
}


QString getPassword()
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    QString password = ini->value("Account/Password", "").toString();
    /*
    QString decPassword;
    for (int i = 0; i < encPassword.length(); i++)
        decPassword.push_back(encPassword.at(i).toAscii() - (encPassword.length() - i));
    */
    return password;
}
void setPassword(QString password)
{
    /*
    QString encPassword;
    for (int i = 0; i < password.length(); i++)
        encPassword.push_back(password.at(i).toAscii() + (password.length() - i));
    */
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    ini->setValue("Account/Password", password);
}


int getUpdateInterval()
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    return ini->value("Network/UpdateInterval", 20).toInt();
}
void setUpdateInterval(int updateInterval)
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    ini->setValue("Network/UpdateInterval", updateInterval);
}

bool getSnapToEdges()
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    return ini->value("Interface/SnapToEdges", true).toBool();
}
void setSnapToEdges(bool snapToEdges)
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    ini->setValue("Interface/SnapToEdges", snapToEdges);
}

QString getLanguage()
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    return ini->value("Interface/Language", "ru").toString();
}
void setLanguage(QString lang)
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    ini->setValue("Interface/Language", lang);
}

bool getAlwaysOnTop()
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    return ini->value("Interface/AlwaysOnTop", true).toBool();
}
void setAlwaysOnTop(bool alwaysOnTop)
{
    QSettings *ini = new QSettings("info.ini", QSettings::IniFormat);
    ini->deleteLater();
    ini->setValue("Interface/AlwaysOnTop", alwaysOnTop);
}

void setValue(QString key, QVariant value)
{
    QSettings ini("info.ini", QSettings::IniFormat);
    ini.setValue(key, value);
}


int getAutorunState()
{
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (reg.value("Byfly-Agent", 0).toString() == qApp->applicationFilePath())
        return autorunForAllUsers;
    QSettings reg2("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (reg2.value("Byfly-Agent", 0).toString() == qApp->applicationFilePath())
        return autorunForCurrentUser;
    return autorunDisabled;
}
void setAutorunState(int autorun)
{
    QSettings *reg;
    if (autorun == autorunDisabled)
    {
        reg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->remove("Byfly-Agent");
        delete reg;
        reg = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->remove("Byfly-Agent");
        delete reg;
    }
    else if (autorun == autorunForCurrentUser)
    {
        setAutorunState(autorunDisabled);
        reg = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->setValue("Byfly-Agent", qApp->applicationFilePath());
        delete reg;
    }
    else if (autorun == autorunForAllUsers)
    {
        setAutorunState(autorunDisabled);
        reg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        reg->setValue("Byfly-Agent", qApp->applicationFilePath());
        delete reg;
    }
}
}
