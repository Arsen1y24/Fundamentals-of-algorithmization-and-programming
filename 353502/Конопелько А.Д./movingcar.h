#ifndef MOVINGCAR_H
#define MOVINGCAR_H

#include <QObject>
#include "MyHeaders.h"

class MovingCar : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MovingCar(QObject *parent = nullptr);
    QTimer* carTimer;
    void startMoving();
    void moveFirstSlot();
    void moveSecondSlot();
    ~MovingCar();

signals:
    void updateScene();
    void addGoblin();

private:
    void moveFirst();
    void moveSecond();
    void ex_code();
    void goblinGo();
};

#endif // MOVINGCAR_H
