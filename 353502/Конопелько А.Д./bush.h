#ifndef BUSH_H
#define BUSH_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>

class Bush : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bush(QObject *parent = nullptr);

signals:
};

#endif // BUSH_H
