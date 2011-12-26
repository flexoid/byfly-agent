#include <QApplication>
#include <QTextCodec>
#include <QObject>
#include <QTranslator>

#include "view.h"
#include "scene.h"
#include "http.h"
#include "controller.h"
#include "settingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/lang_" + SettingsFile::getLanguage());
    a.installTranslator(&translator);

    a.setApplicationName(QObject::tr("byfly • Agent", "ApplicationName"));
    a.setQuitOnLastWindowClosed(false);

    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForCStrings(codec);

    Scene *scene = Scene::instance();
    View *view = View::instance();

    Http *http = Http::instance();

    Controller *controller = Controller::instance();

    QObject::connect(http, SIGNAL(balansReceived(QString)),
            controller, SLOT(updateBalance(QString)));

    QObject::connect(http, SIGNAL(timeReceived(QString)),
            controller, SLOT(updateTime(QString)));

    QObject::connect(http, SIGNAL(trafficReceived(QString)),
            controller, SLOT(updateTraffic(QString)));

    QObject::connect(http, SIGNAL(incorrectSettings()),
                     controller, SLOT(incorrectSettings()));

    QObject::connect(http, SIGNAL(maxSessionsError()),
                     controller, SLOT(maxSessionsError()));

    QObject::connect(http, SIGNAL(incorrectLogin()),
                     controller, SLOT(incorrectLogin()));

    QObject::connect(http, SIGNAL(unknownError()),
                     controller, SLOT(unknownError()));


    QTimer::singleShot(1000, http, SLOT(getBalance()));
    QObject::connect(controller->timer, SIGNAL(timeout()),
                     http, SLOT(getBalance()));

    return a.exec();
}

