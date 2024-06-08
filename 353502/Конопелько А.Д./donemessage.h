#ifndef DONEMESSAGE_H
#define DONEMESSAGE_H

#include <QObject>
#include "MyHeaders.h"

class DoneMessage : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit DoneMessage(QObject *parent = nullptr);

signals:

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap* pixMessage;
};

#endif // DONEMESSAGE_H
