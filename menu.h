#ifndef MENU_H
#define MENU_H

#include <QApplication>
#include <QObject>
#include <QMenu>

#include "settingsdialog.h"
#include "controller.h"
#include "http.h"

class Menu : public QObject
{
    Q_OBJECT

public:
    Menu(QObject *parent = 0);
    void showMenu(const QPoint &pos);

};

#endif // MENU_H
