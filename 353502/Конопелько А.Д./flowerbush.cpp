#include "flowerbush.h"

FlowerBush::FlowerBush(QObject *parent)
    : QObject{parent}
{
    QPixmap pix_l(":bush2.png");
    setPos(1240, 530);
    setPixmap(QPixmap(pix_l.scaled(700, 440)));
}
