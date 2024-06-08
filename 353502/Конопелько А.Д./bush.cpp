#include "bush.h"

Bush::Bush(QObject *parent)
    : QObject{parent}
{
    QPixmap pix_l(":bush1.png");
    setPos(-300, 600);
    setPixmap(QPixmap(pix_l.scaled(700, 440)));
}
