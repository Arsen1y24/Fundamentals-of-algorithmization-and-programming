#ifndef POCKET_H
#define POCKET_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>

class Pocket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Pocket(QObject *parent = nullptr);

signals:
};

#endif // POCKET_H
