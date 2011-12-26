#include "settings.h"

Settings::Settings()
{
}

QString SettingsFile::getLogin()
{
    QSettings ini("info.ini", QSettings::IniFormat);
    return ini.value("User/Login", 0).toString();
}

QString SettingsFile::getPassword()
{
    QSettings ini("info.ini", QSettings::IniFormat);
    return ini.value("User/Password", 0).toString();
}
