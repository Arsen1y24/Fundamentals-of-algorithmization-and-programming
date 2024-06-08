#include "donemessage.h"

DoneMessage::DoneMessage(QObject *parent)
    : QObject{parent}
{}

QRectF DoneMessage::boundingRect() const
{
    return QRectF(0, 0, 200, 200);
}

void DoneMessage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixMessage(":donePixmap.png");
    painter->drawPixmap(0, 0, 120, 120, pixMessage);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}
