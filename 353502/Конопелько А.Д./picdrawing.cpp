#include "picdrawing.h"

PicDrawing::PicDrawing(QObject *parent)
    : QObject{parent}
{
    QPixmap pix_l(":drawing.png");
    setPos(0, 0);
    setPixmap(QPixmap(pix_l.scaled(90, 40)));
}
