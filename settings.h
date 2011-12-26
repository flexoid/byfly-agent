#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class SettingsFile : public QObject
{
public:
    SettingsFile();
    static QString getLogin();
    static QString getPassword();
};

#endif // SETTINGS_H
