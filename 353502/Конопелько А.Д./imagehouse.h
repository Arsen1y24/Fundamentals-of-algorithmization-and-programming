#ifndef IMAGEHOUSE_H
#define IMAGEHOUSE_H

#include <QObject>
#include "MyHeaders.h"
#include "picdrawing.h"

class ImageHouse : public QObject, public QGraphicsItem, public QPixmap
{
    Q_OBJECT
public:
    explicit ImageHouse(QObject *parent = nullptr);

signals:
    void goToRoom(int endRoom);
    void signalTakeMarker();
    void signalTakeClips();
    void showClips();
    void hideClips();
    void showMarker();
    void hideMarker();
    void guyUsesClips();
    void deleteClips();
    void guyUsesMarker();
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void isInRoom_3();
    void isInRoom_1();
    void isInRoom_2();
    void markerIsClicked();
    void clipsAreClicked();
    void isNotInRoom_1();
    void isNotInRoom_2();
    void slotNowMayClick();

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool nowInRoom_1;
    bool nowInRoom_2;
    bool handIsClips = false;
    bool handIsMarker = false;
    bool canUseMarker = false;
    bool canUseClips = false;
    bool mayClick = true;

    QPixmap* thisHouse;
    bool canITakeMarker = false;
    bool canITakeClips = false;
    bool cursorIsHand = false;
    bool markerIsInBag = false;
    bool clipsAreInBag = false;
    bool clipsAreUseless = false;
    bool markerIsUseless = false;
    QCursor myCurs;

    // QGraphicsItem interface
protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // IMAGEHOUSE_H
