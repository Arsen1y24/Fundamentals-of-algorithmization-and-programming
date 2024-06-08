#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 1600, 900, this);
    ui->graphicsView->resize(1930, 930);
    ui -> graphicsView -> setScene(scene);
    startForm = new DialogStart();
    connect(startForm, &DialogStart::signalStart, this, &MainWindow::startDrawing);
    startForm->setModal(true);
    startForm->exec();
                            //this->showFullScreen(); // из-за этого вэйлэнд не поддерживает
}

void MainWindow::startDrawing()
{
    onceNotice = true;
    qDebug() << "drawing";
    if(loseForm != nullptr){
        delete(loseForm);
        loseForm = nullptr;
    }
    startForm->close();
    delete(startForm);
    startForm = nullptr;
    drawScene();
    markerOnScene = new MarkerImage();
    markerOnSceneExists = true;
    scene->addItem(markerOnScene);
    clipsOnScene = new ClipsImage;
    clipsOnSceneExist = true;
    scene->addItem(clipsOnScene);
    spriteGuy = new Sprite();
    spriteGuyExists = true;
    scene->addItem(spriteGuy);
    gr = new GraphMe();
    scene->addItem(gr);

    myCar = new MovingCar();
    myCarExists = true;
    myCar->setZValue(10);
    scene -> addItem(myCar);

    connect(myCar, &MovingCar::updateScene, this, &MainWindow::updScene);
    connect(this, &MainWindow::startCarMovingFirst, myCar, &MovingCar::moveFirstSlot);
    connect(myCar, &MovingCar::addGoblin, this, &MainWindow::addGoblinOnScene);

    connect(spriteGuy, &Sprite::updateScene, this, &MainWindow::updScene);
    connect(iHouse, &ImageHouse::goToRoom, spriteGuy, &Sprite::guyGoMakeVec);
    connect(spriteGuy, &Sprite::findWaySignal, gr, &GraphMe::vecFromTo);
    connect(gr, &GraphMe::shareVecToGo, spriteGuy, &Sprite::getVecToGo);
    connect(spriteGuy, &Sprite::signalIsInRoom_3, iHouse, &ImageHouse::isInRoom_3);

    connect(iHouse, &ImageHouse::signalTakeClips, clipsOnScene, &ClipsImage::clipsInTheBag);
    connect(iHouse, &ImageHouse::signalTakeMarker, markerOnScene, &MarkerImage::markerInTheBag);

    connect(spriteGuy, &Sprite::signalIsInRoom_1, iHouse, &ImageHouse::isInRoom_1);
    connect(spriteGuy, &Sprite::signalIsNotInRoom_1, iHouse, &ImageHouse::isNotInRoom_1);
    connect(iHouse, &ImageHouse::hideClips, clipsOnScene, &ClipsImage::slotHideClips);
    connect(iHouse, &ImageHouse::showClips, clipsOnScene, &ClipsImage::slotShowClips);
    connect(iHouse, &ImageHouse::guyUsesClips, spriteGuy, &Sprite::guyUseClipsOnBed);
    connect(clipsOnScene, &ClipsImage::clickOnClips, iHouse, &ImageHouse::clipsAreClicked);
    connect(iHouse, &ImageHouse::deleteClips, this, &MainWindow::slotDelClips);

    connect(spriteGuy, &Sprite::signalIsInRoom_2, iHouse, &ImageHouse::isInRoom_2);
    connect(spriteGuy, &Sprite::signalIsNotInRoom_2, iHouse, &ImageHouse::isNotInRoom_2);
    connect(iHouse, &ImageHouse::hideMarker, markerOnScene, &MarkerImage::slotHideMarker);
    connect(iHouse, &ImageHouse::showMarker, markerOnScene, &MarkerImage::slotShowMarker);
    connect(iHouse, &ImageHouse::guyUsesMarker, spriteGuy, &Sprite::guyUseMarkerOnPicture);
    connect(markerOnScene, &MarkerImage::clickOnMarker, iHouse, &ImageHouse::markerIsClicked);
    connect(spriteGuy, &Sprite::deleteMarker, this, &MainWindow::slotDelMarker);
    connect(spriteGuy, &Sprite::messageMarker, this, &MainWindow::slotMessageMarker);
    connect(spriteGuy, &Sprite::signalShowPic, this, &MainWindow::drawPic);
    connect(spriteGuy, &Sprite::hadDrawn, iHouse, &ImageHouse::slotNowMayClick);
    connect(spriteGuy, &Sprite::signalSharePosition, this, &MainWindow::getMyPosition);
    connect(this, &MainWindow::signalGoblinNotices, spriteGuy, &Sprite::stopMoving);

    QTimer::singleShot(400, this, [=](){
        emit startCarMovingFirst();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawScene()
{
    /*
    if(goblinExists){
        qDebug() << "1__";
        delete(goblin);
        goblin = nullptr;
    }

    if(spriteGuyExists){
        qDebug() << "2__";
        delete(spriteGuy);
        spriteGuy = nullptr;
    }
    if(markerOnSceneExists){
            qDebug() << "3__";
        delete(markerOnScene);
        markerOnScene = nullptr;
    }
    if(clipsOnSceneExist){
            qDebug() << "4__";
        delete(clipsOnScene);
        clipsOnScene = nullptr;
    }
    if(picDrawExists){
            qDebug() << "5__";
        delete(picDraw);
        picDraw = nullptr;
    }
    if(myCarExists){
            qDebug() << "6__";
        //delete(myCar);
        //myCar = nullptr;
    }

    // if(myMessageExists){
    //         qDebug() << "7__";
    //     delete(myMessage);
    //     myMessage = nullptr;
    // }
    // if(picDrawExists){
    //     qDebug() << "8__";
    //     delete(picDraw);
    //     picDraw = nullptr;
    // }
*/
    qDebug() << " dOOOOne";
    iHouse = new ImageHouse;
    scene->addItem(iHouse);
    scene->update();
    fBush = new FlowerBush();
    bush = new Bush();
    tree = new Tree();
    pocketClips = new Pocket();
    pocketMarker = new Pocket();
    pocketClips->setPos(1360, 50);
    pocketMarker->setPos(1360, 260);
    fBush->setZValue(16);
    bush->setZValue(17);
    tree->setZValue(15);
    scene->addItem(pocketClips);
    scene->addItem(pocketMarker);
    scene->addItem(tree);
    scene->addItem(bush);
    scene->addItem(fBush);

    scene->update();
    timerRelations = new QTimer();
    connect(timerRelations, &QTimer::timeout, this, &MainWindow::checkRelations);
    timerRelations->start(10);
}

void MainWindow::checkRelations()
{
    if(xMyPos > 900 && yMyPos == 648){
        return;
    }
    // qDebug() << xMyPos << " " << xGobPos << " ( " << (xMyPos - xGobPos) * dirGob << " ) " << yMyPos << " " << yGobPos;
    if(dirGob != 0 && onceNotice){
        if(((xMyPos - xGobPos) * dirGob < 300) && (xMyPos - xGobPos) * dirGob > 0 && (abs(yMyPos - yGobPos) < 68)){
            onceNotice = false;
            qDebug() << "notices" << xMyPos;
            emit signalGoblinNotices(xMyPos - xGobPos, yMyPos - yGobPos);
            timerRelations->stop();
        }
    }
}

void MainWindow::updScene()
{
    scene->update();
}

void MainWindow::addGoblinOnScene()
{
    goblin = new SpriteGoblin();
    scene->addItem(goblin);
    connect(goblin, &SpriteGoblin::updateScene, this, &MainWindow::updScene);
    connect(iHouse, &ImageHouse::deleteClips, goblin, &SpriteGoblin::clipsSetReady);
    connect(goblin, &SpriteGoblin::signalSeePic, this, &MainWindow::clearPic);
    connect(spriteGuy, &Sprite::hadDrawn, goblin, &SpriteGoblin::drawingSetReady);
    connect(goblin, &SpriteGoblin::deletePic, this, &MainWindow::clearPic);
    connect(goblin, &SpriteGoblin::signalShareGoblinPosition, this, &MainWindow::getGobPosition);
    connect(this, &MainWindow::signalGoblinNotices, goblin, &SpriteGoblin::goToEat);
    connect(goblin, &SpriteGoblin::eatingSignal, goblin, &SpriteGoblin::eatingSlot);
    connect(goblin, &SpriteGoblin::eatingSignal, spriteGuy, &Sprite::deadSlot);
    connect(goblin, &SpriteGoblin::eatingSignal, this, [=](){
        delete(spriteGuy);
        spriteGuy = nullptr;
        spriteGuyExists = false;
    });
    connect(goblin, &SpriteGoblin::signalYouLose, this, &MainWindow::showImageYouLose);
    connect(goblin, &SpriteGoblin::signalYouWin, this, &MainWindow::showImageYouWin);
}

void MainWindow::slotDelClips()
{
    myMessage = new DoneMessage();
    myMessage->setPos(1190, 310);
    scene->addItem(myMessage);
    QTimer::singleShot(700, this, &MainWindow::closeMessage);
    clipsOnSceneExist = false;
    delete(clipsOnScene);
    clipsOnScene = nullptr;
}

void MainWindow::slotDelMarker()
{
    delete(markerOnScene);
    markerOnSceneExists = false;
    markerOnScene = nullptr;
}

void MainWindow::slotMessageMarker()
{
    myMessage = new DoneMessage();
    myMessageExists = true;
    myMessage->setPos(900, 600);
    scene->addItem(myMessage);
    QTimer::singleShot(700, this, &MainWindow::closeMessage);
}

void MainWindow::closeMessage()
{
    myMessageExists = false;
    delete(myMessage);
    myMessage = nullptr;
}

void MainWindow::drawPic()
{
    picDraw = new PicDrawing();
    picDrawExists = true;
    picDraw->setPos(830, 605);
    scene->addItem(picDraw);
}

void MainWindow::clearPic()
{
    delete(picDraw);
    picDrawExists =false;
    picDraw = nullptr;
}

void MainWindow::getMyPosition(int xPosition, int yPosition)
{
    xMyPos = xPosition;
    yMyPos = yPosition;
}

void MainWindow::getGobPosition(int xGobPosition, int yGobPosition, int directionGob)
{
    xGobPos = xGobPosition;
    yGobPos = yGobPosition;
    dirGob = directionGob;
}

void MainWindow::showImageYouLose()
{
    loseForm = new DialogLose();
    loseForm->raise();
    loseForm->setModal(true);
    loseForm->exec();
}

void MainWindow::showImageYouWin()
{
    winForm = new DialogWin();
    winForm->raise();
    winForm->setModal(true);
    winForm->exec();
}

void MainWindow::on_pushButton_clicked()
{
    QApplication::exit();
}
