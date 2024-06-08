#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include "MyHeaders.h"

class Sprite: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite(QObject* parent = nullptr);
    void guyGoToRoom(int nextRoom);
    void guyGoMakeVec(int endRoom);

public slots:
    void nextFrame();
    void getVecToGo(QVector<int> vecToShare);
    void guyUseClipsOnBed();
    void guyUseMarkerOnPicture();
    void nextPicFrame();
    void stopMoving(int xDistance, int yDistance);
    void deadSlot();
signals:
    void updateScene();
    void findWaySignal(int currentRoom, int endRoom);
    void signalIsInRoom_3();
    void signalIsInRoom_1();
    void signalIsNotInRoom_1();
    void signalIsInRoom_2();
    void signalIsNotInRoom_2();
    void messageMarker();
    void signalShowPic();
    void deleteMarker();
    void hadDrawn();
    void signalSharePosition(int xPosition, int yPosition);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    void whatToDo();
    QPointF* pos;
    int direction; // 1 - left, 2 - right, 3 - up, 4 - down
    int columnChange = 0;
    int dYFrame = 0;
    QTimer* spriteTimer;
    QTimer* picTimer;
    QPixmap* spriteImage;
    int currentFrame;
    int it;
    int dix = 0, diy = 0, ix = 0, iy = 0;
    int xPos;
    int yPos;
    int xStop;
    int yStop;
    int currentRoom;
    int nextRoom;
    int endNumRoom;
    int endChangedDirection;
    bool check = false;
    bool isWalkingNow;
    bool wantToChangeDirection;
    bool checkOneSignalCall_3 = true;
    bool checkOneSignalCall_1 = true;
    bool checkOneSignalCall_2 = true;
    bool drawsPicture = false;
    QVector<QPoint> vecRooms;
    QVector<int> vecWay;
};

#endif // SPRITE_H
