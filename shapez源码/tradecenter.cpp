#include "tradecenter.h"
#include"map.h"
#include<QDebug>
#include <QRandomGenerator>

TradeCenter::TradeCenter(int init_id_x, int init_id_y, QObject* parent)
    : QObject(parent), QGraphicsPixmapItem() {
    QPixmap tradeCenterImage(":/image/image/tradecenter.png");
    setPixmap(tradeCenterImage.scaled(2 * TileSize, 2 * TileSize));
    setPos((init_id_x) * TileSize, (init_id_y) * TileSize);
    setZValue(1);
}
void TradeCenter::setMap(Map *m){map =m;}
TradeCenter::~TradeCenter()
{
}


Mission::Mission(bool init,Map *m, QGraphicsScene *s):map(m),scene(s),idItem(nullptr),curItem(nullptr),targetItem(nullptr)
{
    if(init)
        missionUpdate(1);
}

Mission::~Mission()
{
    // qDebug()<<"start ~mission";
    if(picItem)
    {
        delete picItem;
        picItem = nullptr;
    }
    if(curItem)
    {
        delete curItem;
        curItem = nullptr;
    }
    if(targetItem)
    {
        delete targetItem;
        targetItem = nullptr;
    }
    // qDebug()<<"end ~mission";
}

void Mission::missionUpdate(int id)
{
    ID = id;
    cur = 0;
    if(id == 1)
    {
        target = 20;
        itemID = 1;
    }
    if(id == 2)
    {
        target = 20;
        itemID = 2;
    }
    if(id == 3)
    {
        target = 30;
        itemID = 4;
    }
    if(id>=4)
    {
        itemID = QRandomGenerator::global()->bounded(1, 6);  // 生成 [1, 6] 范围内的随机整数
        if(itemID == 3)
            target = QRandomGenerator::global()->bounded(3, 16);
        else
            target = QRandomGenerator::global()->bounded(20, 41);  // 生成 [20, 40] 范围内的随机整数

    }
    updateItem(ID,target,cur,itemID);
}

void Mission::updateItem(int id, int TargetNum, int CurNum, int ItemID)
{
    ID = id;
    target = TargetNum;
    cur = CurNum;
    itemID = ItemID;
    if (scene->items().contains(idItem))
        scene->removeItem(idItem);
    if (scene->items().contains(targetItem))
        scene->removeItem(targetItem);
    if (scene->items().contains(curItem))
        scene->removeItem(curItem);
    if (scene->items().contains(picItem))
        scene->removeItem(picItem);


    idItem = new QGraphicsTextItem(QString::number(id));
    idItem->setFont(QFont("Arial", 18, QFont::Bold));
    idItem->setDefaultTextColor(Qt::white);
    idItem->setPos(TileSize * MapWidth +144, 128*5);

    curItem = new QGraphicsTextItem(QString::number(CurNum));
    curItem->setFont(QFont("Arial", 18, QFont::Bold));
    curItem->setDefaultTextColor(Qt::white);
    curItem->setPos(TileSize * MapWidth +144, 128*6);

    targetItem = new QGraphicsTextItem(QString::number(TargetNum));
    targetItem->setFont(QFont("Arial", 18, QFont::Bold));
    targetItem->setDefaultTextColor(Qt::white);
    targetItem->setPos(TileSize * MapWidth +128, 128*6+64);

    switch(ItemID){
    case 1:
        picItem = new QGraphicsPixmapItem(QPixmap(":/image/image/ironItem.png").scaled(64, 64));
        break;
    case 2:
        picItem = new QGraphicsPixmapItem(QPixmap(":/image/image/diamondItem.png").scaled(64, 64));

        break;
    case 3:
        picItem = new QGraphicsPixmapItem(QPixmap(":/image/image/netheriteItem.png").scaled(64, 64));
        break;
    case 4:
        picItem = new QGraphicsPixmapItem(QPixmap(":/image/image/ironPiece.png").scaled(64, 64));
        break;
    case 5:
        picItem = new QGraphicsPixmapItem(QPixmap(":/image/image/shit.png").scaled(64, 64));
        break;
    default:
        break;
    }
    picItem->setPos(TileSize * MapWidth+128, 128*5+64);
    scene->addItem(idItem);
    scene->addItem(targetItem);
    scene->addItem(curItem);
    scene->addItem(picItem);

}

void Mission::deliver(int id)
{
    if(itemID == id){
        cur++;
        scene->removeItem(curItem);
        curItem = new QGraphicsTextItem(QString::number(cur));
        curItem->setFont(QFont("Arial", 18, QFont::Bold));
        curItem->setDefaultTextColor(Qt::white);
        curItem->setPos(TileSize * MapWidth +144, 128*6);
        scene->addItem(curItem);
    }
    if(cur>=target)
    {
        qDebug()<<"Mission"<<ID<<"completed";
        map->addMoney(10+ID/5);
        missionUpdate(ID+1);
    }
}

QGraphicsPixmapItem *Mission::getpicItem() {return picItem;}
QGraphicsTextItem *Mission::gettargetItem() {return targetItem;}
QGraphicsTextItem *Mission::getcurItem() {return curItem;}
QGraphicsTextItem *Mission::getIdItem() {return idItem;}

int Mission::getID() const
{
    return ID;
}

int Mission::getTarget() const
{
    return target;
}

int Mission::getCur() const
{
    return cur;
}

int Mission::getItemID() const
{
    return itemID;
}


