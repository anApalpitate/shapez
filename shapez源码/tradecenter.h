// tradecenter.h
#ifndef TRADECENTER_H
#define TRADECENTER_H
#include <QObject>
#include <QGraphicsPixmapItem>
class Map;
class TradeCenter : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    TradeCenter(int init_id_x, int init_id_y, QObject* parent = nullptr);
    ~TradeCenter();

    void setInitValue(QGraphicsTextItem* v1,QGraphicsTextItem* v2);
    void setMap(Map* map);

private:
    Map* map;
    int curVal;
signals:
};
class Mission{
public:
    Mission(bool init,Map*map,QGraphicsScene* scene);
    ~Mission();
    void missionUpdate(int id);
    void updateItem(int ID,int target,int cur,int itemID);
    void deliver(int itemID);
    QGraphicsPixmapItem* getpicItem();
    QGraphicsTextItem* gettargetItem();
    QGraphicsTextItem* getcurItem();
    QGraphicsTextItem *getIdItem() ;

    int getID()const;
    int getTarget()const;
    int getCur()const;
    int getItemID()const;
private:
    Map*map;
    int ID;
    int target;
    int cur;
    int itemID;
    QGraphicsTextItem* idItem;
    QGraphicsPixmapItem* picItem;
    QGraphicsTextItem* targetItem;
    QGraphicsTextItem* curItem;
    QGraphicsScene* scene;
};

#endif // TRADECENTER_H
