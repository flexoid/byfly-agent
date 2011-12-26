#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QTimer>

#include "view.h"
#include "scene.h"
#include "settingsfile.h"
#include "settingsdialog.h"

class Controller : public QObject
{
    Q_OBJECT

protected:
    Controller();

public:
    static Controller* _self;
    static Controller* instance()
    {
        if(!_self) _self = new Controller();
        return _self;
    }

    QTimer *timer;

    static void writeLog(int level, QString text);
    static const int Notice = 1;
    static const int Warning = 2;
    static const int Error = 3;
    static const int Critical = 4;

private:
    Scene *scene;

public slots:
    void updateBalance(QString balance);
    void updateTime(QString time);
    void updateTraffic(QString traffic);
    void incorrectSettings();
    void maxSessionsError();
    void incorrectLogin();
    void unknownError();
    void openSettingsWidget();
    void about();
    void quit();

private slots:
    void updateSettings();
};

#endif // CONTROLLER_H
