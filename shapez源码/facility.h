// facility.h

#ifndef FACILITY_H
#define FACILITY_H
#include "tile.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QQueue>
class Tile;
class Item;
class Facility : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Facility(Tile* tile,QGraphicsScene* scene,int RL);
    ~Facility();
    int getType() const;
    Tile* getTile() const;
    Tile* getOutputTile() const;
    QPixmap getpic() const;
    int getTileX() const;
    int getTileY() const;
    int getRL() const;
    QGraphicsScene* getScene() const;
    void setTile(Tile* tile);
    void setOutPutTile(Tile* tile);
    void Update();
    virtual void intake(Item* item);
protected:
    int type;
    int TileX;
    int TileY;
    int RL;
    QGraphicsScene* scene;
    Tile* curTile;
    Tile* NextTile;
    QPixmap pic;
};
class Belt : public Facility {
    Q_OBJECT

public:
    Belt(Tile* tile, QGraphicsScene* scene,int RL);
    ~Belt();
};
class Trash : public Facility {
    Q_OBJECT

public:
    Trash(Tile* tile, QGraphicsScene* scene,int RL);
private:
};

class Miner : public Facility {
    Q_OBJECT
public:
    Miner(Tile* tile, QGraphicsScene* scene,int RL);
    ~Miner();
    void dig();
private:
    QTimer* miningTimer;
};
class Cutter2:public Facility{
public:
    Cutter2(Tile* tile, QGraphicsScene* scene, int RL);
    void output();
private:
};
class Cutter:public Facility{
public:
    Cutter(Tile* tile,QGraphicsScene* scene,int RL);
    ~Cutter();
    void setC2(Cutter2* c);
    void intake(Item* item);
    void output();
private:
    Cutter2* c2;
    QQueue<int> queue;
    QTimer* workTimer;
};
class Composter:public Facility{
public:
    explicit Composter(Tile* tile,QGraphicsScene* scene,int RL);
    ~Composter();
    void intake(Item* item);
    void output();
private:
    QQueue<int> queue;
    QTimer* workTimer;
};

#endif // FACILITY_H
