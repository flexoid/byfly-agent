#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QApplication>

namespace SettingsFile
{
    QString getLogin();
    void setLogin(QString login);
    
    QString getPassword();
    void setPassword(QString password);
    
    int getUpdateInterval();
    void setUpdateInterval(int updateInterval);
    
    bool getSnapToEdges();
    void setSnapToEdges(bool snapToEdges);

    bool getAlwaysOnTop();
    void setAlwaysOnTop(bool alwaysOnTop);

    QString getLanguage();
    void setLanguage(QString lang);

    template <typename T> T getValue(QString key)
    {
        QSettings ini("info.ini", QSettings::IniFormat);
        return ini.value(key).value<T>();
    }

    void setValue(QString key, QVariant value);

    static const int autorunDisabled = 0;
    static const int autorunForCurrentUser = 1;
    static const int autorunForAllUsers = 2;
    int getAutorunState();
    void setAutorunState(int autorun);

}

#endif // SETTINGS_H
