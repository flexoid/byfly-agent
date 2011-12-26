#include "graphbutton.h"

GraphButton::GraphButton(const QPixmap & pixmap, QGraphicsScene *scene, QGraphicsItem * parent)
        : QGraphicsPixmapItem(pixmap, parent, scene)
{
    this->setAcceptHoverEvents(true);
}

void GraphButton::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    qApp->quit();
    //this->setPixmap(QPixmap(":/images/button_close_pressed.png"));
    QGraphicsPixmapItem::mousePressEvent(event);
}

void GraphButton::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    //this->setPixmap(QPixmap(":/images/button_close_normal.png"));
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void GraphButton::hoverEnterEvent (QGraphicsSceneHoverEvent * event)
{
    //this->setPixmap(QPixmap(":/images/close2.png"));
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void GraphButton::hoverLeaveEvent (QGraphicsSceneHoverEvent * event)
{
    //this->setPixmap(QPixmap(":/images/close.png"));
    QGraphicsPixmapItem::hoverLeaveEvent(event);

}
