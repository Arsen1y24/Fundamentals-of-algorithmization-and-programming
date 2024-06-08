#ifndef GRAPHME_H
#define GRAPHME_H

#include <QObject>
#include "MyHeaders.h"

class GraphMe : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit GraphMe(QObject *parent = nullptr);

signals:
    void shareVecToGo(QVector<int> vecToShare);
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void vecFromTo(int beg, int end);
private:
    QVector<QPair<int, int>> vecRooms[5];

};

#endif // GRAPHME_H
