#ifndef GRAPHBUTTON_H
#define GRAPHBUTTON_H

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

class GraphButton : public QGraphicsPixmapItem
{
    //Q_OBJECT

public:
    GraphButton(const QPixmap & pixmap, QGraphicsScene *scene = 0, QGraphicsItem * parent = 0);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent * event);
};

#endif // GRAPHBUTTON_H
