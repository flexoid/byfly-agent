#include "menu.h"

Menu::Menu(QObject *parent)
        : QObject(parent)
{
}

void Menu::showMenu(const QPoint &pos)
{
    QMenu menu;
    menu.addAction(tr("Update"), Http::instance(), SLOT(getBalance()));
    menu.addSeparator();
    menu.addAction(tr("Options..."), Controller::instance(), SLOT(openSettingsWidget()));
    menu.addSeparator();
    menu.addAction(tr("About"), Controller::instance(), SLOT(about()));
    menu.addSeparator();
    menu.addAction(tr("Exit"), Controller::instance(), SLOT(quit()));

    menu.exec(pos);
}
