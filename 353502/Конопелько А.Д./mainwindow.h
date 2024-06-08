#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "movingcar.h"
#include "sprite.h"
#include "graphme.h"
#include "imagehouse.h"
#include "markerimage.h"
#include "clipsimage.h"
#include "spritegoblin.h"
#include "donemessage.h"
#include "bush.h"
#include "flowerbush.h"
#include "tree.h"
#include "pocket.h"

#include "dialogwin.h"
#include "dialoglose.h"
#include "dialogstart.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updScene();
    void addGoblinOnScene();
    void slotDelClips();
    void slotDelMarker();
    void slotMessageMarker();
    void closeMessage();
    void drawPic();
    void clearPic();
    void getMyPosition(int xPosition, int yPosition);
    void getGobPosition(int xGobPosition, int yGobPosition, int directionGob);
    void showImageYouLose();
    void showImageYouWin();
    void startDrawing();
    void on_pushButton_clicked();

signals:
    void startCarMovingFirst();
    void startCarMovingSecond();
    void signalGoblinNotices(int xDistance, int yDistance);
private:
    int xMyPos = 100;
    int yMyPos = 100;
    int xGobPos = 0;
    int yGobPos = 0;
    int dirGob = 1;
    bool spriteGuyExists = false;
    bool goblinExists = false;
    bool myCarExists = false;
    bool markerOnSceneExists = false;
    bool clipsOnSceneExist = false;
    bool myMessageExists = false;
    bool onceNotice = true;
    bool picDrawExists = false;
    Ui::MainWindow *ui;

    QTimer *timer;
    QTimer* timerRelations;
    QPainter *paint;
    QGraphicsScene* scene;
    QPixmap* pixmapHouse;
    Sprite* spriteGuy;
    SpriteGoblin* goblin;
    MovingCar* myCar;
    GraphMe* gr;
    ImageHouse* iHouse;
    MarkerImage* markerOnScene;
    ClipsImage* clipsOnScene;
    QPixmap* clipsDone;
    DoneMessage* myMessage;
    PicDrawing* picDraw;
    FlowerBush* fBush;
    Bush* bush;
    Tree* tree;
    Pocket* pocketClips;
    Pocket* pocketMarker;
    DialogWin* winForm;
    DialogLose* loseForm;
    DialogStart* startForm;
    void drawScene();
    void checkRelations();
};
#endif // MAINWINDOW_H
