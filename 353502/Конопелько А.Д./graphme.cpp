#include "graphme.h"

GraphMe::GraphMe(QObject *parent)
    : QObject{parent}
{
    vecRooms[1].append(QPair(0, 325));
    vecRooms[0].append(QPair(1, 325));

    vecRooms[1].append(QPair(2, 440));
    vecRooms[2].append(QPair(1, 440));

    vecRooms[3].append(QPair(2, 320));
    vecRooms[2].append(QPair(3, 360));

    vecRooms[2].append(QPair(4, 325));
    vecRooms[4].append(QPair(2, 325));
}

QRectF GraphMe::boundingRect() const
{
    return QRectF(0, 0, 1160, 1560);
}

void GraphMe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // painter->drawRect(QRect(620, 240, 330, 260)); // 0
    // painter->drawRect(QRect(950, 240, 300, 260)); // 1
    // painter->drawRect(QRect(295, 520, 320, 280)); // 4

    // painter->setPen(Qt::yellow);
    // painter->drawRect(QRect(1160, 700, 80, 50));
    // painter->drawRect(QRect(1110, 650, 80, 50));
    // painter->drawRect(QRect(970, 410, 220, 80));
    // painter->drawRect(QRect(780, 545, 130, 100));


    // // pockets

    // painter->setPen(Qt::black);
    // QPoint points[4]; // 2
    // points[0] = QPoint(620, 520);
    // points[1] = QPoint(620, 800);
    // points[2] = QPoint(946, 800);
    // points[3] = QPoint(1190, 520);
    // QPolygon pol;
    // pol << QPoint(points[0]) << QPoint(points[1]) << QPoint(points[2]) <<
    //     QPoint(points[3]);
    // painter -> drawPolygon(pol);

    // QPoint points1[4]; // 3
    // points1[0] = QPoint(1190, 520);
    // points1[1] = QPoint(1270, 520);
    // points1[3] = QPoint(946, 800);
    // points1[2] = QPoint(1270, 800);
    // QPolygon pol1;
    // pol1 << QPoint(points1[0]) << QPoint(points1[1]) << QPoint(points1[2]) << QPoint(points1[3]);
    // painter -> drawPolygon(pol1);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void GraphMe::vecFromTo(int beg, int end)
{
    // BFS
    std::queue <int> myQueue;
    myQueue.push(beg);
    int numOfVertices = 5;
    QVector<bool> used(numOfVertices);
    QVector<int> d(numOfVertices), p(numOfVertices);
    used[beg] = true;
    p[beg] = -1;
    while (!myQueue.empty()) {
        int v = myQueue.front();
        myQueue.pop();
        for (int i = 0; i < vecRooms[v].size(); i++) {
            int to = vecRooms[v][i].first;
            if (!used[to]) {
                used[to] = true;
                myQueue.push (to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }
    QVector<int> path;
    for (int v = end; v != -1; v = p[v])
        path.push_back(v);
    std::reverse (path.begin(), path.end());
    emit shareVecToGo(path);
}
