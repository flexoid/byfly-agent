#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QBitmap>
#include <QDebug>
#include <QWindowStateChangeEvent>

#include "menu.h"
#include "settingsfile.h"
#include "controller.h"
#include "http.h"

class View : public QGraphicsView
{
    Q_OBJECT

protected:
    View(QWidget * parent = 0);

public:
    static View* _self;
    static View* instance()
    {
        if(!_self) _self = new View();
        return _self;
    }

    inline void setSnapEnabled(bool enabled) { SnapEnabled = enabled; }
    inline void setSnapFactor(int factor) { snapFactor = factor; }

    QPixmap bgpixmap;
    QGraphicsPixmapItem *background;

    QTranslator translator;

private:
    inline bool isAnymoreSnapped(int num);

    //--Snap to screen----
    bool SnapEnabled;
    bool isSnaped[4];
    int snapFactor;
    //--------------------

    //--Drag'n'Drop----
    bool DragEnabled;
    bool ClickedOnItem;
    QPoint m_ptPosition;
    //-----------------


protected:
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent(QMouseEvent* pe);
    virtual void resizeEvent(QResizeEvent *);

signals:
    void sceneAdded(QGraphicsView *view);

public slots:
    void updateSettings();

};

#endif // VIEW_H
