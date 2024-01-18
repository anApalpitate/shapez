#ifndef ITEM_H
#define ITEM_H
#include"tile.h"
#include <QObject>
#include <QGraphicsPixmapItem>
class Item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Item(Tile* tile,QGraphicsScene* scene,QObject *parent = nullptr);
    ~Item();
    void act();
    void setTile(Tile* tile);
    void start();
    void animateMove(const QVariant& value);
    virtual bool cuttable();
    QString getName()const;
    int getIdX()const;
    int getIdY()const;
    int getId()const;
protected:
    int CoinVal;
    int MoneyVal;
    bool startVal;
    Tile* curTile;
    QGraphicsScene* scene;
    Map* map;
    QString name;
    int id;
    int HP;
    int MaxHP;
    QTimer* moveTimer;
};
class Iron:public Item{

public:
    explicit Iron(Tile* tile,QGraphicsScene* scene,QObject *parent = nullptr);
    bool cuttable();
};
class Diamond:public Item{

public:
    explicit Diamond(Tile* tile,QGraphicsScene* scene,QObject *parent = nullptr);
    bool cuttable();
};
class Netherite:public Item{
public:
    explicit Netherite(Tile* tile,QGraphicsScene* scene,QObject *parent = nullptr);
    bool cuttable();
};
class IronPiece:public Item{
public:
    explicit IronPiece(Tile* tile,QGraphicsScene* scene,QObject *parent = nullptr);
    bool cuttable();
};
class Shit:public Item{
public:
    explicit Shit(Tile* tile,QGraphicsScene* scene,QObject *parent = nullptr);
    bool cuttable();
};
#endif // ITEM_H
