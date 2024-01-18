#include "item.h"
#include"facility.h"
#include"map.h"
#include<QDebug>
#include<QPixmap>
#include<QPropertyAnimation>
Item::Item(Tile* tile,QGraphicsScene* scene, QObject* parent)
    : QObject(parent), QGraphicsPixmapItem(), curTile(tile), scene(scene),map(tile->getMap()),startVal(0),CoinVal(0),MoneyVal(0),name("Item"),MaxHP(5),id(0)
{
    setPos(tile->pos());
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Item::act);
    moveTimer->start(MoveSpeed+MoveSpeed/50);
    HP = MaxHP;
}

Item::~Item()
{
    // qDebug()<<"~item";
    scene->removeItem(this);
    map->removeItem(this);
    moveTimer->stop();
    delete moveTimer;

}
void Item::act()
{
    // 如果当前地块为空或 "Trash"，则自我销毁
    if (!curTile) {
        delete this;
        return;
    }
    int t = curTile->getType();
    if(t == 2)
    {
        delete this ;
        return;
    }
    else if(t==0)
    {
        map->addCoin(CoinVal*CoinRate);
        map->addMoney(MoneyVal);
        map->getMission()->deliver(id);
        delete this;
        return;
    }
    Tile* nextTile = map->getTileNeibour(curTile,curTile->getRL());
    if (!nextTile) {
        // qDebug()<<"edge";
        delete this;
        return;
    }
    else if (t == 1||startVal) {
        HP = MaxHP;
        startVal = 0;
        QVariantAnimation* animation = new QVariantAnimation(this);
        animation->setStartValue(pos());
        animation->setEndValue(nextTile->pos());
        animation->setDuration(MoveSpeed);  // 设置动画时长，单位为毫秒
        connect(animation, &QVariantAnimation::valueChanged, this, &Item::animateMove);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        // 更新当前地块为下一个地块
        curTile = nextTile;
    }
    //如果当前地块为空或者为部分器械则物品不运动
    else if(t == 4&&id == 1)
    {
        curTile->facility->intake(this);
    }
    else if(t==5&&id==5)
    {
        curTile->facility->intake(this);
    }
    //其余情况物品不动
    HP--;
    if(HP<=0)
        delete this;
    return ;
}
void Item::animateMove(const QVariant& value)
{
    setPos(value.toPointF());
}

bool Item::cuttable(){return 0;}

QString Item::getName() const{return name;}

int Item::getIdX() const{return curTile->getIdX();}

int Item::getIdY() const{return curTile->getIdY();}

int Item::getId() const{return id;}
void Item::setTile(Tile* newTile){curTile = newTile;}

void Item::start(){startVal =1;}

Iron::Iron(Tile *tile, QGraphicsScene *scene, QObject *parent)
    : Item(tile, scene, parent)
{
    CoinVal = 5;
    MoneyVal = 0;
    setPixmap(QPixmap(":/image/image/ironItem.png").scaled(TileSize, TileSize));
    scene->addItem(this);
    setZValue(5);
    name = "Iron";
    id=1;
    HP = MaxHP= 5;
    map->addItem(this);
}

bool Iron::cuttable(){return true;}

Diamond::Diamond(Tile *tile, QGraphicsScene *scene, QObject *parent):Item(tile,scene,parent)
{
    CoinVal = 10;
    MoneyVal = 0;
    setPixmap(QPixmap(":/image/image/diamondItem.png").scaled(TileSize,TileSize));
    scene->addItem(this);
    setZValue(6);
    name = "Diamond";
    id=2;
    HP = MaxHP= 10;
    map->addItem(this);
}
bool Diamond::cuttable(){return false;}


Netherite::Netherite(Tile *tile, QGraphicsScene *scene, QObject *parent)
    :Item(tile,scene,parent)
{
    CoinVal = 20;
    MoneyVal = 1;
    setPixmap(QPixmap(":/image/image/netheriteItem.png").scaled(TileSize,TileSize));
    scene->addItem(this);
    setZValue(7);
    name = "Netherite";
    id=3;
    HP = MaxHP= 50;
    map->addItem(this);
}
bool Netherite::cuttable(){return false;}

IronPiece::IronPiece(Tile *tile, QGraphicsScene *scene, QObject *parent):Item(tile,scene,parent)
{
    CoinVal = 10;
    MoneyVal = 0;
    setPixmap(QPixmap(":/image/image/ironPiece.png").scaled(TileSize,TileSize));
    scene->addItem(this);
    setZValue(8);
    name = "IronPiece";
    id=4;
    HP = MaxHP= 10;
    map->addItem(this);
}

bool IronPiece::cuttable(){return false;}


Shit::Shit(Tile *tile, QGraphicsScene *scene, QObject *parent):Item(tile,scene,parent)
{
    CoinVal = -10;
    MoneyVal = -1;
    setPixmap(QPixmap(":/image/image/shit.png").scaled(TileSize,TileSize));
    scene->addItem(this);
    setZValue(9);
    name = "Shit";
    id=5;
    HP = MaxHP=3;
    map->addItem(this);
}
bool Shit::cuttable(){return false;}
