#include "pocket.h"

Pocket::Pocket(QObject *parent)
    : QObject{parent}
{
    QPixmap pix_l(":pocket.png");
    //setPos(0, 0);
    setPixmap(QPixmap(pix_l.scaled(320, 350)));
}
