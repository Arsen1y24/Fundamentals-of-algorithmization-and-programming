#include "imagehouse.h"

ImageHouse::ImageHouse(QObject *parent)
    : QObject{parent}
{
    setCursor(myCurs);
}

QRectF ImageHouse::boundingRect() const
{
    return QRectF(0, 0, 1660, 1560);
}

void ImageHouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap1(":house_N.jpg");
    painter->drawPixmap(0, 0, 1400, 900, pixmap1);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void ImageHouse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!mayClick){
        return;
    }
    QPointF ptr = mapToScene(event->pos());
    double y = ptr.ry();
    double x = ptr.rx();
    if((x > 620 && x < 950) && y > 240 && y < 500){
        emit goToRoom(0);
        canITakeMarker = false;
        canITakeClips = false;
    }
    else if((x > 950 && x < 1250) && y > 240 && y < 500){
        emit goToRoom(1);
        canITakeMarker = false;
        canITakeClips = false;
    }
    else if((x > 295 && x < 615) && y > 520 && y < 800){
        emit goToRoom(4);
        canITakeMarker = false;
        canITakeClips = false;
    }
    else if((x > 620 && x < 1190) && (y > 520 && y < 800) && y < -70 * x / 61 + 115020 / 61){
        qDebug() << "\n\n*" << x << " " << y;
        emit goToRoom(2);
        canITakeMarker = false;
        canITakeClips = false;
    }
    else if((x > 940 && x < 1270) && (y > 520 && y < 800) && y > -70 * x / 61 + 115020 / 61){
        if(canITakeMarker){
            if(x > 1160 && x < 1240 && (y > 700 && y < 750) && !markerIsInBag){
                this -> setCursor(QCursor(QPixmap(":cursorHand.png").scaled(50, 50)));
                cursorIsHand = true;
                markerIsInBag = true;
                emit signalTakeMarker();
                qDebug() << " В рюкзак маркер";
                canUseMarker = true;//////////////// OK!
            }
        }
        if(canITakeClips){
            if(x > 1110 && x < 1190 && (y > 650 && y < 700) && !clipsAreInBag){
                this -> setCursor(QCursor(QPixmap(":cursorHand.png").scaled(50, 50)));
                cursorIsHand = true;
                clipsAreInBag = true;
                emit signalTakeClips();
                canUseClips = true; // ////////////////////////// OK!
                qDebug() << " В рюкзак скрепки";
            }
            else{
                handIsClips = false;
            }
        }
        qDebug() << "\n\n&" << x << " " << y;
        emit goToRoom(3);
    }
    if(nowInRoom_1 && handIsClips){
        if((x > 970 && x < 970 + 220) && (y > 410 && y < 490)){
            emit guyUsesClips();
            qDebug() << "Используешь clips на кровати";
            clipsAreUseless = true;
            handIsClips = false;
            this -> setCursor(QCursor(Qt::ArrowCursor));
            emit deleteClips();
        }
    }
    qDebug() << nowInRoom_2 << handIsMarker;
    if(nowInRoom_2 && handIsMarker){
        if((x > 780 && x < 910) && (y > 545 && y < 645)){
            mayClick = false;
            qDebug() << "Используешь маркер на картине";
            emit guyUsesMarker();
            markerIsUseless = true;
            handIsMarker = false;
            this -> setCursor(QCursor(Qt::ArrowCursor));
        }
        else{
            handIsMarker = false;
        }
    }
    if(handIsMarker){
        handIsMarker = false;
    }
    else if(handIsClips){
        handIsClips = false;
    }
}

void ImageHouse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this -> setCursor(QCursor(Qt::ArrowCursor));
    cursorIsHand = false;
    Q_UNUSED(event);
}

void ImageHouse::isInRoom_3()
{
    int x = myCurs.pos().rx();
    int y = myCurs.pos().ry();
    if(!markerIsInBag)
        canITakeMarker = true;
    if(!clipsAreInBag)
        canITakeClips = true;
    if(canITakeClips){
        if((x > 1110 && x < 1190 && (y > 650 && y < 700)) && !clipsAreInBag){ // CLIPS
            this -> setCursor(QCursor(QPixmap(":cursorHand.png").scaled(70, 70)));
            cursorIsHand = true;
        }
    }
    if(canITakeMarker){
        if((x > 1160 && x < 1240 && (y > 700 && y < 750)) && !markerIsInBag){
            this -> setCursor(QCursor(QPixmap(":cursorHand.png").scaled(50, 50)));
            cursorIsHand = true;
        }
    }
    if(cursorIsHand){
        if(!(x > 1160 && x < 1240 && (y > 700 && y < 750))){
            this -> setCursor(QCursor(Qt::ArrowCursor));
            cursorIsHand = false;
        }
        if(!(x > 1110 && x < 1190 && (y > 650 && y < 700))){ /// ABOUt clips
            this -> setCursor(QCursor(Qt::ArrowCursor));
            cursorIsHand = false;
        }
    }
}

void ImageHouse::isInRoom_1()
{
    qDebug() << " is in Room 1";
    // if(markerIsInBag)
    //     canUseMarker = true;
    if(clipsAreInBag)
        canUseClips = true;
    nowInRoom_1 = true;
}

void ImageHouse::isInRoom_2()
{
    qDebug() << " is in Room 2";
    if(markerIsInBag)
        canUseMarker = true;
    // if(clipsAreInBag)
    //     canUseClips = true;
    nowInRoom_2 = true;
}

void ImageHouse::markerIsClicked()
{
    if(canUseMarker){
        qDebug() << "Берешь из рюкзака маркер";
        if(handIsMarker){
            handIsMarker = false;
            this -> setCursor(QCursor(Qt::ArrowCursor));
        }
        else if(handIsClips){
            handIsMarker = true;
            handIsClips = false;
           qDebug() << "MMМMMArker";
            this->setCursor(QCursor(QPixmap(":imageMarker").scaled(70, 70)));
        }
        else{
            handIsMarker = true;
            this->setCursor(QCursor(QPixmap(":imageMarker").scaled(70, 70)));
        }
    }
}

void ImageHouse::clipsAreClicked()
{
    if(canUseClips){
        qDebug() << "Берешь из рюкзака кнопки";
        if(handIsClips){
            qDebug() << 1111;
            handIsClips = false;
            this -> setCursor(QCursor(Qt::ArrowCursor));
        }
        else if(handIsMarker){
            qDebug() << 2222;
            handIsMarker = false;
            handIsClips = true;
            qDebug() << "MMМышка CCскрепkки";
            this->setCursor(QCursor(QPixmap(":paperClips").scaled(70, 70)));
        }
        else{
            qDebug() << 3333;
            handIsClips = true;
                qDebug() << "Мышка скрепки";
                this->setCursor(QCursor(QPixmap(":paperClips").scaled(70, 70)));
        }
    }
}

void ImageHouse::isNotInRoom_1()
{
    nowInRoom_1 = false;
}

void ImageHouse::isNotInRoom_2()
{
    nowInRoom_2 = false;
}

void ImageHouse::slotNowMayClick()
{
    mayClick = true;
}
