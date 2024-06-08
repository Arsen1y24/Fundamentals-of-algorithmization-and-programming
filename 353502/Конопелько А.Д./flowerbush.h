#ifndef FLOWERBUSH_H
#define FLOWERBUSH_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>

class FlowerBush : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit FlowerBush(QObject *parent = nullptr);

signals:
};

#endif // FLOWERBUSH_H
