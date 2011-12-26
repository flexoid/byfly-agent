#include "animimage.h"

AnimImage* AnimImage::_self = 0;

AnimImage::AnimImage()
{
    pixmap = new QGraphicsPixmapItem(0, Scene::instance());
    pixmap->show();
    pixmap->setPos(8, 23);
    movie = new QMovie(":/images/loadbar.gif");
    movie->start();
    connect(movie, SIGNAL(frameChanged(int)), this, SLOT(animUpdated()));
    animUpdated();
}

void AnimImage::animUpdated()
{
    pixmap->setPixmap(movie->currentPixmap());
}

void AnimImage::show()
{
    pixmap->show();
}

void AnimImage::hide()
{
    pixmap->hide();
}
