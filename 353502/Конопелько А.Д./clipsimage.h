#ifndef CLIPSIMAGE_H
#define CLIPSIMAGE_H

#include <QObject>
#include "MyHeaders.h"

class ClipsImage : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ClipsImage(QObject *parent = nullptr);
    void slotHideClips();
    void slotShowClips();

signals:
    void clickOnClips();
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void clipsInTheBag();

private:
    QPixmap* clipsImage;
    QPixmap pixClips;
    int xSize;
    int xPos;
    int yPos;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CLIPSIMAGE_H
