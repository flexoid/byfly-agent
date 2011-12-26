#include "scene.h"

Scene* Scene::_self = 0;

Scene::Scene(QObject * parent)
        : QGraphicsScene(parent)
{
}

void Scene::updateItems(QGraphicsView *view)
{
    //QFont byflyLogoTextFont("Arial", 15);
    QFont infoFont("Arial", 9);
    QFont alphaFont("Arial", 18);
    //QFont madeByFont("Arial", 6);

    /*byflyLogoText = this->addText("", byflyLogoTextFont);
    byflyLogoText->setHtml("<div align=right><i><font color=\"#E1712C\">by</font><font color=\"#0E498A\">fly</font></i>." + QString("Агент") + "</div>");
    byflyLogoText->setPos(20,0);
    */

    balanceText = this->addText("", infoFont);
    balanceText->setHtml("<font color=blue>" + tr("Balance:") + " </font><font color=#d76b00>" + tr("getting...") + "</font>");
    balanceText->setPos(15,22);
    
    timeText = this->addText("", infoFont);
    timeText->setHtml("<font color=blue>" + tr("Time:") + " </font><font color=#d76b00>" + tr("getting...") + "</font>");
    timeText->setPos(15,35);

    trafficText = this->addText("", infoFont);
    trafficText->setHtml("<font color=blue>" + tr("Traffic:") + " </font><font color=#d76b00>" + tr("getting...") + "</font>");
    trafficText->setPos(15,48);
    trafficText->show();

    /*QGraphicsTextItem *alpha = this->addText("", alphaFont);
    alpha->setHtml("<font color=red>тестирование</font>");
    alpha->setPos(-7, 50);
    alpha->rotate(-20);
    alpha->setOpacity(0.2);*/
}

