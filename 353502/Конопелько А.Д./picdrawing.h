#ifndef PICDRAWING_H
#define PICDRAWING_H

#include <QObject>
#include "MyHeaders.h"

class PicDrawing : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit PicDrawing(QObject *parent = nullptr);

signals:
};

#endif // PICDRAWING_H
