#ifndef ANIMIMAGE_H
#define ANIMIMAGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QMovie>
#include <QGraphicsScene>
#include "scene.h"

class AnimImage : public QObject
{
    Q_OBJECT

public:
    static AnimImage* instance()
    {
        if(!_self) _self = new AnimImage();
        return _self;
    }
    void show();
    void hide();

public slots:
    void animUpdated();

private:
    AnimImage();
    static AnimImage* _self;
    QMovie *movie;
    QGraphicsPixmapItem *pixmap;
};

#endif // ANIMIMAGE_H
