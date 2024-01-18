#include "facility.h"
#include "item.h"
#include <QDebug>
#include <QString>
#include <QRandomGenerator>

Facility::Facility(Tile *tile, QGraphicsScene *scene, int RL)
    : QGraphicsPixmapItem(), type(-1), RL(RL), scene(scene), curTile(tile), NextTile(tile->getTileNeibour(RL))
{
    setTile(tile);
    setPos(tile->pos());
    setZValue(2);
    curTile->setType(-1);
}
Facility::~Facility()
{
    curTile->setType(-1);
    curTile->facility = nullptr;
}

int Facility::getType() const { return type; }
Tile *Facility::getTile() const { return curTile; }
Tile *Facility::getOutputTile() const { return NextTile; }
QPixmap Facility::getpic() const { return pic; }
int Facility::getTileX() const { return TileX; }
int Facility::getTileY() const { return TileY; }

int Facility::getRL() const { return RL; }
QGraphicsScene *Facility::getScene() const { return scene; }

void Facility::setTile(Tile *tile)
{
    if (tile != nullptr)
    {
        curTile = tile;
        TileX = tile->getIdX();
        TileY = tile->getIdY();
        setPos(tile->pos()); // 将设备放置在新的Tile的位置
    }
}
void Facility::setOutPutTile(Tile *tile) { NextTile = tile; }

void Facility::Update()
{
    setOutPutTile(curTile->getTileNeibour(RL));
}

void Facility::intake(Item *item) { delete item; }

Belt::Belt(Tile *tile, QGraphicsScene *scene, int RL)
    : Facility(tile, scene, RL)
{
    type = 1;
    curTile->setType(1);
    QPixmap beltPixmap(":/image/image/belt_" + QString::number(RL) + ".png");
    setPixmap(beltPixmap.scaled(40, 40));
    qDebug() << "Add belt at" << tile->getIdX() << tile->getIdY() << "RotateLevel:" << RL;
}
Belt::~Belt()
{
}

Trash::Trash(Tile *tile, QGraphicsScene *scene, int RL)
    : Facility(tile, scene, RL)
{
    type = 2;
    curTile->setType(2);
    QPixmap beltPixmap(":/image/image/trash.png");
    setPixmap(beltPixmap.scaled(40, 40));
    qDebug() << "Add trash at" << tile->getIdX() << tile->getIdY() << "RotateLevel:" << RL;
}
Miner::Miner(Tile *tile, QGraphicsScene *scene, int RL)
    : Facility(tile, scene, RL)
{
    type = 3;
    curTile->setType(3);
    QPixmap beltPixmap(":/image/image/miner_" + QString::number(RL) + ".png");
    setPixmap(beltPixmap.scaled(40, 40));
    qDebug() << "Add miner at" << tile->getIdX() << tile->getIdY() << "RotateLevel:" << RL;
    miningTimer = new QTimer(this);
    // 设置定时器
    connect(miningTimer, &QTimer::timeout, this, &Miner::dig);

    // 根据tile的ID启动定时器
    if (tile->getOreId() == 1) // 铁
    {
        miningTimer->start(int(2000 * DigRate));
    }
    else if (tile->getOreId() == 2) // 钻石
    {
        miningTimer->start(int(5000 * DigRate));
    }
    else if (tile->getOreId() == 3) // 下界合金
    {
        miningTimer->start(int(20000 * DigRate));
    }

    // 周期性执行 operate 函数的定时器
}

Miner::~Miner()
{
    miningTimer->stop();
    delete miningTimer;
}

void Miner::dig()
{
    if (!curTile)
    {
        qDebug() << "dig error";
        return;
    }
    switch (curTile->getOreId())
    {
    case 1:
    {
        Iron *iron = new Iron(curTile, scene);
        iron->start();
        // qDebug() << "Succesfully Dig out an iron";
        break;
    }
    case 2:
    {
        Diamond *diamond = new Diamond(curTile, scene);
        diamond->start();
        // qDebug() << "Succesfully Dig out a diamond";
        break;
    }
    case 3:
    {
        Netherite *netherite = new Netherite(curTile, scene);
        netherite->start();
        qDebug() << "Succesfully Dig out a netherite";
        break;
    }
    }
}
Cutter2::Cutter2(Tile *tile, QGraphicsScene *scene, int RL) : Facility(tile, scene, RL)
{
    type = 6;
    curTile->setType(6);
    QPixmap beltPixmap(":/image/image/c2_" + QString::number(RL) + ".png");
    setPixmap(beltPixmap.scaled(40, 40));
    qDebug() << "Add cutter2 at" << tile->getIdX() << tile->getIdY() << "RotateLevel:" << RL;
}

void Cutter2::output()
{
    if (NextTile)
    {
        new Shit(NextTile, scene);
    }
}

Cutter::Cutter(Tile *tile, QGraphicsScene *scene, int RL) : Facility(tile, scene, RL)
{
    type = 4;
    curTile->setType(4);
    QPixmap beltPixmap(":/image/image/c1_" + QString::number(RL) + ".png");
    setPixmap(beltPixmap.scaled(40, 40));
    qDebug() << "Add cutter at" << tile->getIdX() << tile->getIdY() << "RotateLevel:" << RL;
    workTimer = new QTimer(this);
    // 设置定时器
    workTimer->start(int(5000 * CutterRate));
    connect(workTimer, &QTimer::timeout, this, &Cutter::output);
}

Cutter::~Cutter()
{
    queue.clear();
    delete c2;
    workTimer->stop();
    delete workTimer;
}

void Cutter::setC2(Cutter2 *c) { c2 = c; }

void Cutter::intake(Item *item)
{
    if (item->cuttable())
    {
        queue.push_back(1);
        // qDebug() << "an Iron enqueue";
        delete item;
    }
}

void Cutter::output()
{
    if (queue.empty())
        return;
    queue.dequeue();
    if (NextTile)
    {
        new IronPiece(NextTile, scene);
        c2->output();
    }
}

Composter::Composter(Tile *tile, QGraphicsScene *scene, int RL) : Facility(tile, scene, RL)
{
    type = 5;
    curTile->setType(5);
    QPixmap beltPixmap(":/image/image/Composter_" + QString::number(RL) + ".png");
    setPixmap(beltPixmap.scaled(40, 40));
    qDebug() << "Add Composter at" << tile->getIdX() << tile->getIdY() << "RotateLevel:" << RL;
    workTimer = new QTimer(this);
    // 设置定时器
    workTimer->start(5000);
    connect(workTimer, &QTimer::timeout, this, &Composter::output);
}

Composter::~Composter()
{
    queue.clear();
    workTimer->stop();
    delete workTimer;
}

void Composter::intake(Item *item)
{
    if (item->getName() == "Shit")
    {
        queue.push_back(1);
        // qDebug() << "a shit enqueue";
    }
    delete item;
}

void Composter::output()
{
    if (queue.empty())
        return;
    queue.dequeue();
    if (NextTile)
    {
        int randomValue = QRandomGenerator::global()->bounded(100);
        if (randomValue < 5 * ComposterRate)
        {
            new Netherite(NextTile, scene);
        }
    }
}
