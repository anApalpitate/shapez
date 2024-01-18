// tile.cpp

#include "tile.h"
#include "facility.h"
#include "map.h"
#include<QGraphicsScene>
#include <QPainter>

Tile::Tile(QObject *parent, int init_id_x, int init_id_y)
    : QObject(parent), QGraphicsItem(), ID(0), idX(init_id_x), idY(init_id_y), size(TileSize), is_empty(1), facility(nullptr),type(-1)
{
    setFlag(ItemIsSelectable, false);
    setPos(idX * size, idY * size);
    // setName("tile");
    setZValue(0);
}

Tile::~Tile() {
    removefacility();
}


void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, size, size, pixmap);
}

int Tile::getIdX() const {return idX;}
int Tile::getIdY() const {return idY;}
int Tile::getId() const{return ID;}
int Tile::getSize() const {return size;}
int Tile::getOreId() const{return ID;}
Map *Tile::getMap() const{return map; }
const QPixmap& Tile::getPixmap() const {return pixmap;}
Tile *Tile::getTileNeibour(int dir){return map->getTileNeibour(this,dir);}
Tile *Tile::getTileFriend(int dir){return map->getTileFriend(this,dir);}
int Tile::getRL(){
    if(!facility)
        return 0;
    return facility->getRL();
}
int Tile::getType() const{return type;}
void Tile::setIdX(int value) {idX = value;}
void Tile::setIdY(int value) {idY = value;}
void Tile::setSize(int value) {size = value;}
void Tile::setPixmap(const QPixmap& value) {pixmap = value;}
void Tile::setMap(Map *map_){map = map_;}
void Tile::setFacility(Facility *f){facility = f;}
void Tile::setType(const int x){type =x;}
bool Tile::empty(){return is_empty;}
void Tile::filled(){is_empty = 0;}

void Tile::updateFacility()
{
    if (hasFacility()) {
        facility->Update();
    }
}

bool Tile::hasFacility()
{
    return facility != nullptr;
}

bool Tile::isTradeCenter()
{
    return type==0;
}
void Tile::removefacility() {
    if (this->facility&&type>0&&type!=6) {
        if (facility->getScene() != nullptr) {
            facility->getScene()->removeItem(facility);
        }
        delete facility;
        facility = nullptr;
    }
}

QRectF Tile::boundingRect() const {return QRectF(0, 0, size, size);}

//IronOre
IronOre::IronOre(QObject *parent, int init_id_x, int init_id_y)
    : Tile(parent, init_id_x, init_id_y) {
    setPixmap(QPixmap(":/image/image/iron.png").scaled(TileSize, TileSize));
    this->filled();
    ID = 1;
}

IronOre::~IronOre() {
}

void IronOre::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Tile::paint(painter, option, widget);
}


//DiamondOre
DiamondOre::DiamondOre(QObject *parent, int init_id_x, int init_id_y)
    : Tile(parent, init_id_x, init_id_y) {
    setPixmap(QPixmap(":/image/image/diamond.png").scaled(TileSize, TileSize));
    this->filled();
    ID = 2;
}

DiamondOre::~DiamondOre() {
}

void DiamondOre::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Tile::paint(painter, option, widget);
}

//NetheriteOre
NetheriteOre::NetheriteOre(QObject *parent, int init_id_x, int init_id_y)
    : Tile(parent, init_id_x, init_id_y) {
    setPixmap(QPixmap(":/image/image/netherite.png").scaled(TileSize, TileSize));
    this->filled();
    ID = 3;
}

NetheriteOre::~NetheriteOre() {
}

void NetheriteOre::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Tile::paint(painter, option, widget);
}
