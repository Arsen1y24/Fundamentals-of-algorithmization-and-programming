#include "markerimage.h"

MarkerImage::MarkerImage(QObject *parent)
    : QObject{parent}
{
    visible = true;
    markerImage = new QPixmap(":imageMarker.png");
    QTransform transform;
    QTransform trans = transform.rotate(40);
    markerImage = new QPixmap(markerImage->transformed(trans));
    xSize = 60;
    xPos = 1170;
    yPos = 700;
    pixMark = markerImage->scaled(xSize, xSize);
    markerImage = &pixMark;
}

QRectF MarkerImage::boundingRect() const
{
    return QRectF(1420, 300, 200, 200);
}

void MarkerImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(xPos, yPos, *markerImage, 0,  0, xSize, xSize);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MarkerImage::markerInTheBag()
{
    markerImage = new QPixmap(":imageMarker.png");
    xSize = 160;
    xPos = 1450;
    yPos = 330;
    pixMark = markerImage->scaled(xSize, xSize);
    markerImage = &pixMark;
}

void MarkerImage::slotHideMarker()
{
    visible = false;
}

void MarkerImage::slotShowMarker()
{
    visible = true;
}

void MarkerImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(visible){
        emit clickOnMarker();
    }
    Q_UNUSED(event);
}

