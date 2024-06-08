#include "sprite.h"

Sprite::Sprite(QObject* parent):
    QObject(parent), QGraphicsItem()
{
    this->setZValue(2);
    spriteImage = new QPixmap(":spriteGuyLeft.png");
    dix = 0;
    ix = 0;
    iy = 0;
    diy = 0;
    it = 2;
    currentRoom = 4;
    currentFrame = 0;
    spriteTimer = new QTimer();
    vecRooms.append(QPoint(630, 370 - 12)); // 0
    vecRooms.append(QPoint(1100, 370 - 12)); // 1
    vecRooms.append(QPoint(810, 660 - 12)); // 2
    vecRooms.append(QPoint(1140, 660 - 12)); // 3
    vecRooms.append(QPoint(460, 660 - 12)); // 4
    connect(spriteTimer, &QTimer::timeout, this, &Sprite::nextFrame);
    spriteTimer -> start(80);
    isWalkingNow = false;
}

void Sprite::nextFrame()
{
    xPos = vecRooms[currentRoom].rx() + ix;
    yPos = vecRooms[currentRoom].ry() + iy;
    if(!isWalkingNow){
        if(currentRoom == 3 && checkOneSignalCall_3){
            qDebug() << "now in room # 3";
            checkOneSignalCall_3 = false;
            emit signalIsInRoom_3();
        }
        else if(currentRoom == 1 && checkOneSignalCall_1){
            qDebug() << "now in room # 1";
            checkOneSignalCall_1 = false;
            emit signalIsInRoom_1();
        }
        else if(currentRoom == 2 && checkOneSignalCall_2){
            qDebug() << "now in room # 2";
            checkOneSignalCall_2 = false;
            emit signalIsInRoom_2();
        }
        currentFrame = 160 * 3;
        ix = 0; iy = 0;
    }
    else{
        if(currentRoom == 1){
            emit signalIsNotInRoom_1();
        }
        if(currentRoom == 2){
            emit signalIsNotInRoom_2();
        }
        checkOneSignalCall_3 = true;
        checkOneSignalCall_1 = true;
        checkOneSignalCall_2 = true;
        currentFrame += 160;
        if(currentFrame >= 1920){
            currentFrame = 0;
        }
        if(abs(vecRooms[currentRoom].rx() + ix - xStop) < 2 && abs(vecRooms[currentRoom].ry() + iy - yStop) < 2){
            dix = 0;
            diy = 0;
            currentFrame = 160 * 3;
            currentRoom = vecWay[it-1];
            if(wantToChangeDirection){
                if(vecWay[it-1] == endNumRoom){
                    ix = 0;
                    iy = 0;
                }
                isWalkingNow = false;
                guyGoMakeVec(endChangedDirection);
            }
            else{
                if(vecWay[it-1] != endNumRoom)
                {
                    guyGoToRoom(vecWay[it]);
                    it++;
                }
                else
                {                                       // USELESS ? ? ?
                    // if(currentRoom == 3){
                    //     qDebug() << "nNNNNNNow in room # 3";
                    //     emit signalIsInRoom_3();
                    // }
                    // else if(currentRoom == 1){
                    //     qDebug() << "NNNNNnow In Room # 1";
                    //     emit signalIsInRoom_1();
                    // }
                    ix = 0;
                    iy = 0;
                    isWalkingNow = false;
                }
            }
        }
        ix += dix;
        iy += diy;
    }
    this->update(vecRooms[currentRoom].rx() + ix, vecRooms[currentRoom].ry() + iy, 160, 160);
}

void Sprite::getVecToGo(QVector<int> vecToShare)
{
    vecWay = vecToShare;
    endNumRoom = vecWay.back();
    whatToDo();
}

void Sprite::guyUseClipsOnBed()
{
    spriteImage = new QPixmap(":spriteGuyLeft.png");
    currentFrame = 160;
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(vecRooms[currentRoom].ry() + iy == 591 && vecRooms[currentRoom].rx() + ix == 790)
        emit signalSharePosition(720, 648);
    else{
        emit signalSharePosition(vecRooms[currentRoom].rx() + ix, vecRooms[currentRoom].ry() + iy);
    }
    painter->drawPixmap(vecRooms[currentRoom].rx() + ix,
                        vecRooms[currentRoom].ry() + iy, *spriteImage, currentFrame, 0 + columnChange, 160, 160 + dYFrame);
    emit updateScene();
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::guyUseMarkerOnPicture()
{
    drawsPicture = true;
    ix -= 20; // {}
    iy -= 57; // [][]
    dYFrame = 50;
    // columnChange = 10; // ()()
    spriteTimer->stop();
    picTimer = new QTimer();
    connect(picTimer, &QTimer::timeout, this, &Sprite::nextPicFrame);
    picTimer->start(100);
    currentFrame = 40; // ===
    spriteImage = new QPixmap(":spriteMarkerJump.png");
}

void Sprite::nextPicFrame()
{
    //qDebug() << currentFrame << " " << columnChange;
    currentFrame += 210; // +++++
    if(columnChange == 3 * 210 && currentFrame == 40 + 210 * 3){
        //    qDebug() << "signal Del mark";
        emit deleteMarker();
    }
    if(currentFrame > 210 * 7 + 40){ // +++++
        currentFrame = 40; // ===
        columnChange += 210;  // --
        if(columnChange == 7 * 210 && currentFrame == 40){
            emit signalShowPic();
        }
        if(columnChange > 8 * 210){ // --
            emit messageMarker();
            picTimer->stop();
            dYFrame = 0;
            currentFrame = 0;
            columnChange = 0;
            spriteImage = new QPixmap(":spriteGuyRight.png");
            currentFrame = 160 * 2;
            ix += 20;
            iy += 57;
            //  currentRoom = 2;
            spriteTimer->start(80);
            drawsPicture = false;
            emit hadDrawn();
        }
    }
}

void Sprite::guyGoToRoom(int nextRoom)
{
    ix = 0;
    iy = 0;
    check = false;
    xStop = vecRooms[nextRoom].rx();
    yStop = vecRooms[nextRoom].ry();
    if(currentRoom == 0){
        goRight();
    }
    else if(currentRoom == 1){
        if(nextRoom == 0)
            goLeft();
        else
            goDown();
    }
    else if(currentRoom == 2){
        if(nextRoom == 1)
            goUp();
        else if (nextRoom == 3)
            goRight();
        else
            goLeft();
    }
    else if(currentRoom == 3){
        goLeft();
    }
    else if(currentRoom == 4){
        goRight();
    }
}

void Sprite::guyGoMakeVec(int endRoom)
{
    if(isWalkingNow){
        wantToChangeDirection = true;
        endChangedDirection = endRoom;
        isWalkingNow = true;
    }
    else{
        ix = 0; iy = 0; /// ? ?? ?
        wantToChangeDirection = false;
        int cRoom = currentRoom;
        it = 2;
        vecWay.clear();
        // надо найти путь из currentRoom в endRoom

        isWalkingNow = true;
        if(endRoom == currentRoom){
            isWalkingNow = false;
            return;
        }
        emit findWaySignal(cRoom, endRoom);
    }
}

QRectF Sprite::boundingRect() const
{
    return QRectF(0, 200, 1460, 1160);
}


void Sprite::goLeft()
{
    dix = -10;
    diy = 0;
    currentFrame = 0;
    spriteImage = new QPixmap(":spriteGuyLeft.png");
}

void Sprite::goRight()
{
    dix = 10;
    diy = 0;
    currentFrame = 0;
    spriteImage = new QPixmap(":spriteGuyRight.png");
}

void Sprite::goUp()
{
    dix = 5;
    diy = -5;
    currentFrame = 0;
    spriteImage = new QPixmap(":spriteGuyRight.png");
}

void Sprite::goDown()
{
    dix = -5;
    diy = 5;
    currentFrame = 0;
    spriteImage = new QPixmap(":spriteGuyLeft.png");
}

void Sprite::whatToDo()
{
    check = true;
    for(int i = 1; i < vecWay.size() && check; i++){
        guyGoToRoom(vecWay[i]);
    }
}

void Sprite::stopMoving(int xDistance, int yDistance)
{
 //   qDebug() << *spriteImage;
    qDebug() << " stopMoving ! ! !";
    if(spriteTimer != nullptr)
        spriteTimer->stop();
    if(drawsPicture){
        qDebug() << "stopJump";
        picTimer->stop();
    }

}

void Sprite::deadSlot()
{
    // delete(this);
}
