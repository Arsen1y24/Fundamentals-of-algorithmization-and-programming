#ifndef TREE_H
#define TREE_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>

class Tree : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tree(QObject *parent = nullptr);

signals:
};

#endif // TREE_H
