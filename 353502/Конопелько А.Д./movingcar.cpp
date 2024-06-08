#include "movingcar.h"

MovingCar::MovingCar(QObject *parent)
    : QObject{parent}
{
    QPixmap pix_l(":carWithGoblin1.png");
    setPixmap(QPixmap(pix_l.scaled(340, 200)));
    carTimer = new QTimer();
    setPos(-470, 680);
    carTimer->start(1000/60);
}

void MovingCar::moveFirstSlot()
{
    connect(carTimer, &QTimer::timeout, this, &MovingCar::moveFirst);
}

void MovingCar::moveSecondSlot()
{
    QPixmap pix_l(":carEmpty2.png");
    setPixmap(QPixmap(pix_l.scaled(340, 200)));
    connect(carTimer, &QTimer::timeout, this, &MovingCar::moveSecond);
}

MovingCar::~MovingCar()
{

}

void MovingCar::moveFirst()
{
    if(this->pos().rx() >= 346){
        disconnect(carTimer, &QTimer::timeout, this, &MovingCar::moveFirst);
        QTimer::singleShot(500, this, &MovingCar::ex_code);
    }
    else
        moveBy(4, 0);
}

void MovingCar::ex_code()
{
    emit addGoblin();
    moveSecondSlot();
    moveSecond();
}

void MovingCar::moveSecond()
{
    if(this->pos().rx() >= 1710){
        disconnect(carTimer, &QTimer::timeout, this, &MovingCar::moveSecond);
        emit updateScene();
        delete(carTimer);
        delete(this);
    }
    else{
        moveBy(9, 0);
        if(this->pos().rx() >= 1100)
            emit updateScene();
    }
}
