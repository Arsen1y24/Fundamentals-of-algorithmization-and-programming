#include "spritegoblin.h"

SpriteGoblin::SpriteGoblin(QObject *parent)
    : QObject{parent}
{
    this->setZValue(3);
    spriteGoblinImage = new QPixmap(":spriteGoblin.png");
    goesRight = true;
    //  spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
    dix = 0;
    ix = 0;
    iy = 0;
    diy = 0;
    currentFrame = 0;
    spriteGoblinTimer = new QTimer();
    vecPlaces.append(QPoint(600, 370 - 10)); // 0
    vecPlaces.append(QPoint(1050, 370 - 10)); // 1
    vecPlaces.append(QPoint(790, 660 - 10)); // 2
    vecPlaces.append(QPoint(1140, 660 - 10)); // 3 skip
    vecPlaces.append(QPoint(245, 660 - 10)); // 4
    vecPlaces.append(QPoint(346, 710)); // 5 (start)
    xPos = vecPlaces[5].rx();
    yPos = vecPlaces[5].ry();
    vecGoblinWay = {2, 1, 0, 1, 2, 4};
    connect(spriteGoblinTimer, &QTimer::timeout, this, &SpriteGoblin::nextFrame);
    spriteGoblinTimer -> start(100); // 180
    numberOfAction = 0;
}

SpriteGoblin::~SpriteGoblin()
{

}

QRectF SpriteGoblin::boundingRect() const
{
    return QRectF(0, 400, 1460, 1160);
}

void SpriteGoblin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!(startsGoing && xPos < 600)){
        emit signalShareGoblinPosition(xPos + 10, yPos - 20, direction);
    }
    //qDebug() << oX;
    qDebug() << currentFrame << " " << oX << " " << addToYGoblinSprite;
    painter->drawPixmap(xPos + 10, yPos - 120, ((*(spriteGoblinImage)).scaled(3000, 3000)), currentFrame, 280 + oX, 180, 280 + addToYGoblinSprite);
    emit updateScene();
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void SpriteGoblin::nextFrame()
{
    if(startsGoing){
        numberOfAction = 0;
        direction = 1;
        if(xPos <= 790){
            ix += 8;
            iy -= 1;
            xPos = vecPlaces[5].rx() + ix;
            yPos = vecPlaces[5].ry() + iy;
        }
        else{
            startsGoing = false;
            ix = 0;
            iy = 0;
            //  currentPosition = 2;
            //  spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png"); /// DELETE !! !! ! !
            iterator = 0; // 0 / 4
            this->setZValue(1);
        }
        currentFrame += 185;
        if(currentFrame > 185 * 5){
            currentFrame = 0;
        }
    }
    else{
        switch (iterator){
        case 0:
            numberOfAction = 0;
            direction = 1;
            didntSleep = true;
            ix += 4;
            iy -= 4;
            xPos = vecPlaces[vecGoblinWay[iterator]].rx() + ix;
            yPos = vecPlaces[vecGoblinWay[iterator]].ry() + iy;
            currentFrame += 185;
            if(currentFrame > 185 * 5){
                currentFrame = 0;
            }
            if(xPos >= 1080){
                xPos -= 30;
                iterator++;
                ix = 0;
                iy = 0;
                spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
                goesRight = false;
                currentFrame = 1845 + 185 * 5;
            }
            break;
        case 1:
            numberOfAction = 0;
            direction = -1;
            ix -= 5;
            xPos = vecPlaces[vecGoblinWay[iterator]].rx() + ix;
            yPos = vecPlaces[vecGoblinWay[iterator]].ry() + iy;
            if(xPos <= 585){
                spriteGoblinTimer->stop();
                emit throwRock();
            }
            currentFrame -= 185;
            if(currentFrame < 1845){
                currentFrame = 1845 + 185 * 5;
            }
            break;
        case 2:
            numberOfAction = 0;
            direction = 1;
            ix += 5;
            xPos = vecPlaces[vecGoblinWay[iterator]].rx() + ix;
            yPos = vecPlaces[vecGoblinWay[iterator]].ry() + iy;
            currentFrame += 185;
            if(currentFrame > 185 * 5){
                currentFrame = 0;
            }
            if(xPos > 920 && didntSleep){
                spriteGoblinTimer->stop();
                didntSleep = false;
                emit execClips();
            }
            if(xPos >= 1080){
                iterator++;
                xPos -= 30;
                ix = 0;
                iy = 0;
                currentFrame = 1845 + 185 * 5;
                spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
                goesRight = false;
                oX = 0;
            }
            break;
        case 3:
            numberOfAction = 0;
            direction = -1;
            // qDebug() << xPos;
            ix -= 4;
            iy += 4;
            xPos = vecPlaces[vecGoblinWay[iterator]].rx() + ix;
            yPos = vecPlaces[vecGoblinWay[iterator]].ry() + iy;
            currentFrame -= 185;
            if(currentFrame < 1845){
                currentFrame = 1845 + 185 * 5;
            }
            if(xPos <= 757){
                if(drawingIsDone){
                    emit reactionOnDrawing();
                }
                else{
                    iterator++;
                    ix = 0;
                    iy = 0;
                    // spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
                    currentFrame = 1845 + 185 * 5;
                }
            }
            break;

        case 4:
            numberOfAction = 0;
            direction = -1;
            //      qDebug() << xPos << " " << yPos << " " << ix << " " << iy << " " << currentFrame << " " << oX;
            ix -= 5;
            xPos = vecPlaces[vecGoblinWay[iterator]].rx() + ix;
            yPos = vecPlaces[vecGoblinWay[iterator]].ry() + iy;
            if(xPos < 235){
                emit goblinLaughs();
                break;
            }
            currentFrame -= 185;
            if(currentFrame < 1845){
                currentFrame = 1845 + 185 * 5;
            }
            break;
        case 5:
            numberOfAction = 0;
            direction = 1;
            if(ix == 0){
                spriteGoblinTimer->stop();
                QTimer::singleShot(200,  this, &SpriteGoblin::staysIn_4);
            }
            ix += 5;
            xPos = vecPlaces[vecGoblinWay[iterator]].rx() + ix;
            yPos = vecPlaces[vecGoblinWay[iterator]].ry() + iy;
            if(xPos >= vecPlaces[vecGoblinWay[0]].rx()){
                if(drawingIsDone){
                    emit reactionOnDrawing();
                    break;
                }
                else{
                    iterator = 0;
                    currentFrame = 0;
                    ix = 0;
                    iy = 0;
                }
            }
            currentFrame += 185;
            if(currentFrame > 185 * 5){
                currentFrame = 0;
            }
            break;
        }
    }

    this->update(xPos + 10, yPos - 120, 180, 280);
}

void SpriteGoblin::staysIn_4()
{
    spriteGoblinTimer->start(100); // 180 ?
    spriteGoblinImage = new QPixmap(":spriteGoblin.png");
    goesRight = true;
    currentFrame = 0;
}

void SpriteGoblin::startGoingFrom_4()
{
    numberOfAction = 0;
    currentFrame = 0;
    yPos -= 20;
    oX = 0;
    spriteGoblinImage = new QPixmap(":spriteGoblin.png");
    goesRight = true;
    iterator++;
    ix = 0;
    iy = 0;
    addToYGoblinSprite = 0;
    spriteGoblinTimer->start(100); // 180 ?? ?
}


// reaction on drawing in room 2

void SpriteGoblin::drawingSetReady()
{
    qDebug() << "drawing is ready";
    drawingIsDone = true;
}

void SpriteGoblin::reactionOnDrawing()
{
    direction = 0;
    spriteGoblinTimer->stop();
    QTimer::singleShot(80, this, &SpriteGoblin::execDrawingReaction); // 320
}

void SpriteGoblin::execDrawingReaction()
{
    amountOfHarm++;
    numberOfAction = 1;
    xPos += 50;
    yPos += 30;
    qDebug() << "reaction emits " << iterator;
    timerDrawing = new QTimer();
    if(iterator == 3){
        dCurFrame = -188;
        currentFrame = 1870 + 187 * 5;
    }
    else if(iterator == 5){
        dCurFrame = 188;
        currentFrame = 0;
    }
    oX = 300;
    connect(timerDrawing, &QTimer::timeout, this, &SpriteGoblin::nextDrawReactFrame);
    timerDrawing->start(92); // 250
}

void SpriteGoblin::nextDrawReactFrame()
{
    currentFrame += dCurFrame;
    if (iterator == 3 && currentFrame < 1870 - 188){
        cntTimesReactedDrawing++;
        if(cntTimesReactedDrawing == 2){
            numberOfAction = 0;
            oX = 0;
            iterator++;
            currentFrame = 2773 + 2770 - 2585;
            ix = 0;
            iy = 0;
            xPos -= 30;
            yPos -= 30;
            dCurFrame = 0;
            timerDrawing->stop();
            // spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
            //    currentFrame = 1845 + 185 * 5;
            //  drawingIsDone = false;
            emit deletePic();
            if(amountOfHarm == 2){
                QTimer::singleShot(1000, this, [=](){
                    emit signalYouWin();
                });
            }
            else{
                spriteGoblinTimer->start(100);
                cntTimesReactedDrawing = 0;
                drawingIsDone = false;
            }
        }
        else{
            currentFrame = 1870 + 187 * 5;
        }
    }
    else if(iterator == 5 && currentFrame > 188 * 4){
        cntTimesReactedDrawing++;
        if(cntTimesReactedDrawing == 2){
            numberOfAction = 0;
            oX = 0;
            timerDrawing->stop();
            spriteGoblinTimer->start(100);
            iterator = 0;
            ix = 0;
            iy = 0;
            xPos -= 30;
            yPos -= 30;
            currentFrame = 0;
            dCurFrame = 0;
            //    drawingIsDone = false;
            cntTimesReactedDrawing = 0;
            emit deletePic();
        }
        else{
            currentFrame = 0;
        }
    }
}


// throws rock (money) in room 0

void SpriteGoblin::throwRock()
{
    direction = -1;
    spriteGoblinTimer->stop();
    QTimer::singleShot(80, this, &SpriteGoblin::execRock); // 320
}

void SpriteGoblin::execRock()
{
    numberOfAction = 2;
    timerRock = new QTimer();
    oX = 550;
    currentFrame = 1870 + 187 * 5;
    connect(timerRock, &QTimer::timeout, this, &SpriteGoblin::nextRockFrame);
    timerRock->start(62); // 250
}

void SpriteGoblin::nextRockFrame()
{
    currentFrame -= 187;
    if(cntCurFrame){
        currentFrame--;
    }
    else{
        currentFrame++;
    }
    cntCurFrame ^= 1;
    if(currentFrame < 1860 - 187.5 * 5){
        if(numberOfThrows >= 2){
            oX = 0;
            timerRock->stop();
            spriteGoblinTimer->start(100);
            iterator++;
            ix = 0;
            currentFrame = 0;
            spriteGoblinImage = new QPixmap(":spriteGoblin.png");
            goesRight = true;
            numberOfThrows = 0;
            numberOfAction = 0;
        }
        else{
            numberOfThrows++;
            currentFrame = 1870 + 187 * 5;
        }
    }
}


// goes to bed in room 1

void SpriteGoblin::lieForTime()
{
    qDebug() << "lies";
    timerBed->start(63); // 250
}

void SpriteGoblin::goToBed()
{
    QTimer::singleShot(50, this, &SpriteGoblin::execBed); // 200
}

void SpriteGoblin::execBed()
{
    numberOfAction = 4;
    yPos += 20;
    dCurFrame = -188;
    timerBed = new QTimer();
    spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
    goesRight = false;
    oX = 1700;
    currentFrame = 1870 + 187 * 5;
    connect(timerBed, &QTimer::timeout, this, &SpriteGoblin::nextBedFrame);
    timerBed->start(62); // 250
}

void SpriteGoblin::clipsSetReady()
{
    qDebug() << "clips are ready";
    clipsAreOnBed = true;
}

void SpriteGoblin::execClips()
{
    direction = 0;
    flies = true;
    qDebug() << "wewegw";
    if(clipsAreOnBed){
        amountOfHarm++;
        numberOfAction = 3;
        qDebug() << "Reaction)";
        timerClipsReaction = new QTimer();
        spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
        goesRight = false;
        oX = 300;
        //       yPos -= 12;
        currentFrame = 1870 + 187 * 5;
        connect(timerClipsReaction, &QTimer::timeout, this, &SpriteGoblin::clipsReactionNextFrame);
        timerClipsReaction->start(125); // 100
    }
    else{
        execBed();
    }
}

void SpriteGoblin::stopSleeping()
{
    yPos -= 20;
    qDebug() << "GetUp";
    currentFrame = 0;
    spriteGoblinImage = new QPixmap(":spriteGoblin.png");
    goesRight = true;
    timerBed->stop();
    spriteGoblinTimer->start(100); // 180
    oX = 0;
}

void SpriteGoblin::nextBedFrame()
{
    currentFrame += dCurFrame;
    if(currentFrame < 1870 - 187 * 4 && dCurFrame < 0){
        dCurFrame = 187;
        timerBed->stop();
        QTimer::singleShot(7000, this, &SpriteGoblin::lieForTime);
    }
    if(currentFrame > 1870 + 187 * 5 && dCurFrame > 0){
        timerBed->stop();
        stopSleeping();
    }
}

void SpriteGoblin::clipsReactionNextFrame()
{
    currentFrame -= 187;
    if(currentFrame == 1870 + 187 * 2 && yPos > 240 && up && flies){
        yPos -= 40;
        currentFrame += 187;
        qDebug() << "up";
    }

    if(currentFrame == 1870 + 187 * 2 && yPos >= 210 && yPos < 340 && flies){
        up = false;
        yPos += 40;
        currentFrame += 187;
        qDebug() << "Down";
    }
    if(!up && flies && yPos >= 340){
        flies = false;
        qDebug() << "Stop";
    }
    if(currentFrame < 1870 - 187 && !flies){ /// разве не 187 * 3  ? ?? ? ?
        qDebug() << "лялял";
        timerClipsReaction->stop();
        clipsAreOnBed = false;
        if(amountOfHarm == 2){
            QTimer::singleShot(1000, this, [=](){
                emit signalYouWin();
            });
        }
        //    yPos += 10;
        QTimer::singleShot(975, this, &SpriteGoblin::execBed); // 700
    }
}


// Laugh in room 4 realization

void SpriteGoblin::goblinLaughs()
{
    numberOfAction = 5;
    direction = -1;
    addToYGoblinSprite = -30;
    spriteGoblinTimer->stop();
    laughTimer = new QTimer();
    oX = 1925;
    yPos += 20;
    xPos += 20;
    currentFrame = 1870 + 187 * 5;
    connect(laughTimer, &QTimer::timeout, this, &SpriteGoblin::nextLaughFrame);
    laughTimer->start(45); // 100 ?
}

void SpriteGoblin::nextLaughFrame()
{
    currentFrame -= 187;
    if(currentFrame < 1860){
        if(cntLaughs < 5){
            currentFrame = 1870 + 187 * 5;
            cntLaughs++;
        }
        else{
            qDebug() << "STOPS laugh";
            laughTimer->stop();
            emit startGoingFrom_4();
            cntLaughs = 0;
        }
    }
}


// goes to me

void SpriteGoblin::goToEat(int xDistance, int yDistance)
{
    xToGo = xDistance < 0 ? std::min(0, xDistance + 70) : std::max(0, xDistance - 70);
    yToGo = yDistance * (xToGo / xDistance);
    numToDivide = 120;
    if(xToGo < 200)
        numToDivide = 30;
    if(xToGo < 100)
        numToDivide = 12;
    dXGoToMe = xToGo / numToDivide;
    dYGoToMe = yToGo /numToDivide;
    if(xDistance < -10){
        spriteGoblinTimer->stop();
        dCurFrame = -187;
        currentFrame = 1870 + 187 * 5;
        timerGoToEat = new QTimer();
        connect(timerGoToEat, &QTimer::timeout, this, &SpriteGoblin::nextGoToMeFrame);
        timerGoToEat->start(25); // 100 ?
        spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
        goesRight = false;
    }
    else if(xDistance > 10){
        spriteGoblinTimer->stop();
        dCurFrame = 187;
        currentFrame = 0;
        timerGoToEat = new QTimer();
        connect(timerGoToEat, &QTimer::timeout, this, &SpriteGoblin::nextGoToMeFrame);
        timerGoToEat->start(25); // 100 ?
        spriteGoblinImage = new QPixmap(":spriteGoblin.png");
        goesRight = true;
    }
    else{
        if(goesRight){
            currentFrame = 0;
            dCurFrame = 187;
        }
        else{
            currentFrame = 1870 + 187 * 5;
            dCurFrame = -187;
        }
        spriteGoblinTimer->stop();
        qDebug() << "eats111111";
        emit eatingSignal();
    }
}

void SpriteGoblin::nextGoToMeFrame()
{
    cntAmountEatFrames++;
    if(cntAmountEatFrames == numToDivide){
        qDebug() << " eats";
        emit eatingSignal();
        timerGoToEat->stop();
    }
    xPos += dXGoToMe;
    yPos += dYGoToMe;
    currentFrame += dCurFrame;
    if(xToGo > 0){
        if(currentFrame > 187 * 5){
            currentFrame = 0;
        }
    }
    else{
        if(currentFrame < 1870){
            currentFrame = 1870 + 187 * 5;
        }
    }
}

void SpriteGoblin::eatingSlot()
{
    qDebug() << goesRight;
    yPos += 40;
    xPos += 40;
    oX = 1125;
    if(goesRight){
        //spriteGoblinImage = new QPixmap(":spriteGoblin.png");
        begCurrentFrame = 0;
        currentFrame = 0;
        dCurFrame = 187;
    }
    else{
        //spriteGoblinImage = new QPixmap(":spriteGoblinReverse.png");
        begCurrentFrame = 1870 + 187 * 5;
        currentFrame = 1870 + 187 * 5;
        dCurFrame = -187;
    }
    currentFrame = begCurrentFrame;
    timerEats = new QTimer();
    connect(timerEats, &QTimer::timeout, this, &SpriteGoblin::nextEatingFrame);
    timerEats->start(270);
}

void SpriteGoblin::nextEatingFrame()
{
    qDebug() << currentFrame << " " << goesRight << " " << begCurrentFrame;
    if(amountOfEatenBones >= 1){
        timerEats->stop();
        QTimer::singleShot(1000, this, [=](){
            emit signalYouLose();
        });

    }
    currentFrame += dCurFrame;
    framesEating++;
    if(framesEating > 13){
        currentFrame = begCurrentFrame;
        framesEating = 0;
        amountOfEatenBones++;
    }
}
