#include "clipsimage.h"

ClipsImage::ClipsImage(QObject *parent)
    : QObject{parent}
{
    //visible = true;
    clipsImage = new QPixmap(":paperClips.png");
    xSize = 60;
    xPos = 1120;
    yPos = 680;
    pixClips = clipsImage->scaled(xSize, xSize - 30);
    clipsImage = &pixClips;
}

void ClipsImage::slotHideClips()
{
    qDebug() << " unvisible clips";
}

void ClipsImage::slotShowClips()
{
    //this->visible = true;
}

QRectF ClipsImage::boundingRect() const
{
    return QRectF(1420, 115, 200, 160);
}

void ClipsImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(xPos, yPos, *clipsImage, 0,  0, xSize, xSize);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void ClipsImage::clipsInTheBag()
{
    clipsImage = new QPixmap(":paperClips.png");
    xSize = 260;
    xPos = 1370;
    yPos = 110;
    pixClips = clipsImage->scaled(xSize + 100, xSize);
    clipsImage = &pixClips;
}

void ClipsImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(/*visible && */ xPos == 1370){
        qDebug() << " Click on clips";
        emit clickOnClips();
    }
    Q_UNUSED(event);
}

