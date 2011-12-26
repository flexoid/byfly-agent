#include "view.h"

View* View::_self = 0;

View::View(QWidget * parent)
        : QGraphicsView(Scene::instance(), parent), bgpixmap(":/images/background.png")
{
    QGraphicsScene* scene = Scene::instance();

    connect(this, SIGNAL(sceneAdded(QGraphicsView*)), scene, SLOT(updateItems(QGraphicsView*)));

    this->setFrameShape(QFrame::NoFrame);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->resize(bgpixmap.size());
    this->setStyleSheet("background: transparent"); 
    this->move(SettingsFile::getValue<QPoint>("Data/StartPos"));
    
    background = scene->addPixmap(bgpixmap);
    background->setZValue(-10);

    scene->setSceneRect(background->boundingRect());

    updateSettings();

    isSnaped[0] = false;
    isSnaped[1] = false;
    isSnaped[2] = false;
    isSnaped[3] = false;

    this->sceneAdded(this);
}


void View::mousePressEvent(QMouseEvent* pe)
{
    if (pe->buttons() == Qt::LeftButton && DragEnabled)
    {
        m_ptPosition = pe->pos();
    }
    else if (pe->buttons() == Qt::RightButton)
    {
        Menu menu(this);
        menu.showMenu(pe->globalPos());
    }
    QGraphicsView::mousePressEvent(pe);
}

void View::mouseReleaseEvent(QMouseEvent* pe)
{
    QGraphicsView::mouseReleaseEvent(pe);
}

void View::mouseMoveEvent(QMouseEvent* pe)
{
    if (QApplication::mouseButtons() == Qt::LeftButton && DragEnabled)
    {
        //-----------Snaping----------------------------
        QDesktopWidget desktop;
        int scrHeight = desktop.availableGeometry(desktop.primaryScreen()).height();
        int scrWidth = desktop.availableGeometry(desktop.primaryScreen()).width();
        int top = this->frameGeometry().top();
        int bottom = this->frameGeometry().bottom();
        int left = this->frameGeometry().left();
        int right = this->frameGeometry().right();
        int height = this->frameGeometry().height();
        int width = this->frameGeometry().width();

        if (isSnaped[0] && top >= snapFactor)
            isSnaped[0] = false;
        if (isSnaped[1] && (scrHeight - bottom) >= snapFactor)
            isSnaped[1] = false;
        if (isSnaped[2] && left >= snapFactor)
            isSnaped[2] = false;
        if (isSnaped[3] && (scrWidth - right) >= snapFactor)
            isSnaped[3] = false;

        //--DeSnap----------

        //---Top
        if (isSnaped[0])
        {
            if (pe->pos().y() - m_ptPosition.y() >= snapFactor)
            {
                move(left, snapFactor + 1);
                return;
            }
            else
                if (pe->globalPos().x() - m_ptPosition.x() >= 0 &&
                    pe->globalPos().x() - m_ptPosition.x() <= scrWidth - width)
                    move(pe->globalPos().x() - m_ptPosition.x(), 0);
        }
        //---Bottom
        else if (isSnaped[1])
        {
            if (m_ptPosition.y() - pe->pos().y() >= snapFactor)
            {
                move(left, scrHeight - snapFactor - height - 1);
                return;
            }
            else
                if (pe->globalPos().x() - m_ptPosition.x() >= 0 &&
                    pe->globalPos().x() - m_ptPosition.x() <= scrWidth - width)
                    move(pe->globalPos().x() - m_ptPosition.x(), scrHeight - height);
        }
        //---Left
        else if (isSnaped[2])
        {
            if (pe->pos().x() - m_ptPosition.x() >= snapFactor)
            {
                move(snapFactor + 1, top);
                return;
            }
            else
                if (pe->globalPos().y() - m_ptPosition.y() >= 0 &&
                    pe->globalPos().y() - m_ptPosition.y() <= scrHeight - height)
                    move(0, pe->globalPos().y() - m_ptPosition.y());
        }
        //---Right
        else if (isSnaped[3])
        {
            if (m_ptPosition.x() - pe->pos().x() >= snapFactor)
            {
                move(scrWidth - width - snapFactor - 1, top);
                return;
            }
            else
                if (pe->globalPos().y() - m_ptPosition.y() >= 0 &&
                    pe->globalPos().y() - m_ptPosition.y() <= scrHeight - height)
                    move(scrWidth - width, pe->globalPos().y() - m_ptPosition.y());
        }
        else
            move(pe->globalPos() - m_ptPosition);

        //--Snap----------

        if (SnapEnabled)
        {
            //---Top
            if (!isSnaped[0] && !isAnymoreSnapped(0) && top < snapFactor)
            {
                this->move(left, 0);
                isSnaped[0] = true;
            }
            //---Bottom
            if (!isSnaped[1] && !isAnymoreSnapped(1) && (scrHeight - bottom) < snapFactor)
            {
                this->move(left, (scrHeight - height));
                isSnaped[1] = true;
            }
            //---Left
            if (!isSnaped[2] && !isAnymoreSnapped(2) && left < snapFactor)
            {
                this->move(0, top);
                isSnaped[2] = true;
            }
            //---Right
            if (!isSnaped[3] && !isAnymoreSnapped(3) && (scrWidth - right) < snapFactor)
            {
                this->move((scrWidth - width), top);
                isSnaped[3] = true;
            }
        }
    }
    QGraphicsView::mouseMoveEvent(pe);
}

bool View::isAnymoreSnapped(int num)
{
    for (int x = 0; x < 4; x++)
        if (x != num && isSnaped[x] == true)
            return true;
    return false;
}

void View::resizeEvent(QResizeEvent *e)
{
    setMask(bgpixmap.mask());
    QGraphicsView::resizeEvent(e);
}

void View::updateSettings()
{
    DragEnabled = true;
    SnapEnabled = SettingsFile::getSnapToEdges();
    snapFactor = 20;
    if (SettingsFile::getAlwaysOnTop())
    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
        show();
    }
    else
    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
        show();
    }
}
