// tile.h

#ifndef TILE_H
#define TILE_H
#include<QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include "Val.h"
class Facility;
class Map;
class Tile : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit Tile(QObject *parent = nullptr, int init_id_x = 0, int init_id_y = 0);
    ~Tile();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int getIdX() const;
    int getIdY() const;
    int getId()const;
    int getSize() const;
    int getOreId() const;
    Map* getMap() const ;
    const QPixmap& getPixmap() const;
    Tile* getTileNeibour(int dir);
    Tile* getTileFriend(int dir);
    int getRL();
    int getType() const;
    void setIdX(int value);
    void setIdY(int value);
    void setSize(int value);
    void setPixmap(const QPixmap& value);
    void setMap(Map* map);
    void setFacility(Facility* facility);
    void setType(const int x);
    void removefacility();
    bool hasFacility();
    bool isTradeCenter();
    bool empty();
    void filled();

    void updateFacility();
    QRectF boundingRect() const override;
    Facility* facility;
protected:
    int ID;
    Map* map;
private:
    int idX;
    int idY;
    int size;
    bool is_empty;
    int type;

    QPixmap pixmap;
};
class IronOre : public Tile {
    Q_OBJECT

public:
    IronOre(QObject *parent = nullptr, int init_id_x = 0, int init_id_y = 0);
    ~IronOre() override;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
};

class DiamondOre : public Tile {
    Q_OBJECT

public:
    DiamondOre(QObject *parent = nullptr, int init_id_x = 0, int init_id_y = 0);
    ~DiamondOre() override;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
};

class NetheriteOre : public Tile {
    Q_OBJECT

public:
    NetheriteOre(QObject *parent = nullptr, int init_id_x = 0, int init_id_y = 0);
    ~NetheriteOre() override;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
};
#endif // TILE_H
