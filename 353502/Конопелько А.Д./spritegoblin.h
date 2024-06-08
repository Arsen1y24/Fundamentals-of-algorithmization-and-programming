#ifndef SPRITEGOBLIN_H
#define SPRITEGOBLIN_H

#include <QObject>
#include "MyHeaders.h"

class SpriteGoblin : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SpriteGoblin(QObject *parent = nullptr);
    ~SpriteGoblin();
signals:
    void updateScene();
    void signalSeePic();
    void deletePic();
    void signalShareGoblinPosition(int xGobPosition, int yGobPosition, int directionGob);
    void eatingSignal();
    void signalYouLose();
    void signalYouWin();
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void nextFrame();
    void nextRockFrame();
    void nextBedFrame();
    void clipsSetReady();
    void drawingSetReady();
    void goToEat(int xDistance, int yDistance);
    void eatingSlot();
    void nextEatingFrame();
private:
    bool numberOfAction = -1; // which timer to stop
    bool cntCurFrame = true;
    bool startsGoing = true;
    bool didntSleep = true;
    bool clipsAreOnBed = false;
    bool drawingIsDone = false;
    bool up = true;
    bool flies = true;
    bool goesRight = true;
    int direction = 1; // 1 - right, 0 - stays, -1 - left
    int addToYGoblinSprite = 0;
    int currentFrame = 0;
    int currentPosition;
    int iterator;
    int dix = 0, diy = 0, ix = 0, iy = 0;
    int xPos;
    int yPos;
    int oX = 0;
    int dCurFrame = 0;
    int cntLaughs = 0;
    int numberOfThrows = 0;
    int cntTimesReactedDrawing = 0;
    int dXGoToMe = 0;
    int dYGoToMe = 0;
    int xToGo = 0;
    int yToGo = 0;
    int cntAmountEatFrames = 0;
    int numToDivide = 42;
    int amountOfEatenBones = 0;
    int framesEating = 0;
    int begCurrentFrame = 0;
    int amountOfHarm = 0;
    QPixmap* spriteGoblinImage;
    QTimer* spriteGoblinTimer;
    QTimer* timerRock;
    QTimer* timerBed;
    QTimer* timerClipsReaction;
    QTimer* laughTimer;
    QTimer* timerDrawing;
    QTimer* timerGoToEat;
    QTimer* timerEats;
    QVector<QPoint> vecPlaces;
    QVector<int> vecGoblinWay;
    void funcForWindow();
    void throwRock();
    void execRock();    
    void goToBed();
    void execBed();
    void stopSleeping();
    void lieForTime();
    void execClips();
    void clipsReactionNextFrame();
    void staysIn_4();
    void goblinLaughs();
    void nextLaughFrame();
    void startGoingFrom_4();
    void reactionOnDrawing();
    void execDrawingReaction();
    void nextDrawReactFrame();
    void nextGoToMeFrame();
};

#endif // SPRITEGOBLIN_H
