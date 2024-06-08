#include "tree.h"

Tree::Tree(QObject *parent)
    : QObject{parent}
{
    QPixmap pix_l(":lights.png");
    setPos(-170, 60);
    setPixmap(QPixmap(pix_l.scaled(340, 840)));
}
