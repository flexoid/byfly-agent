#ifndef SCENE_H
#define SCENE_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QDebug>
#include <QFont>

#include "graphbutton.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

protected:
    Scene(QObject * parent = 0);

public:
    static Scene* _self;
    static Scene* instance()
    {
        if(!_self) _self = new Scene();
        return _self;
    }

    QGraphicsTextItem *byflyLogoText;
    QGraphicsTextItem *balanceText;
    QGraphicsTextItem *timeText;
    QGraphicsTextItem *trafficText;

private slots:
    void updateItems(QGraphicsView *view);

};

#endif // SCENE_H
