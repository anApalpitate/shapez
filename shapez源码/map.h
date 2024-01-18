// map.h

#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QDebug>
#include <QPushButton>
#include <QKeyEvent>
#include <QTransform>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>
#include <QPoint>
#include "tradecenter.h"
#include "facility.h"
class MainWindow;
class Store;
class Map : public QWidget {
    Q_OBJECT

public:
    Map(int rows, int columns, int tileSize, MainWindow* mw,QWidget *parent = nullptr);
    Map(int rows, int columns, int tileSize, MainWindow* mw,const QString FilePath,QWidget *parent = nullptr);

    ~Map();

    void init0();

    void test();
    void test(Tile* tile);
    int getRows() const;
    int getCols() const;
    Tile* getTile(int row, int col) const;
    Tile* getTileFromPoint(QPoint point);
    Tile* getTileNeibour(Tile* tile,int direction);
    Tile* getTileFriend(Tile*,int direction);
    TradeCenter* getTradeCenter()const;
    Mission* getMission()const;
    QGraphicsScene* getScene() const;
    void keyPressEvent(QKeyEvent *keyevent) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void addItem(Item* item);
    void removeItem(Item* item);

    void addTradeCenter();
    void addOre();
    void addButtons();
    void addFacility(Tile* tile,int facilityType,int RL);
    void addMoneyAndCoin(bool init,int val);
    void addMission(bool init);
    void setMainWindow(MainWindow* mw);
    void rotateToolContainer();

    void addCoin(int num);
    void addMoney(int num);
private:
    MainWindow* mainwindow;
    int rows;
    int cols;
    int sz;

    QVector<QVector<Tile*>> tiles;
    TradeCenter* tradeCenter;
    QGraphicsScene* scene;
    QGraphicsRectItem* toolArea;

    QVector<QPushButton*> Buttons;
    QPixmap* ToolContainer;
    QGraphicsPixmapItem* ToolContainerItem;
    int ChosenId;
    int rotatelevel;

    QGraphicsTextItem* coinValueItem;
    QGraphicsTextItem* moneyValueItem;
    int coinVal;
    int moneyVal;
    QPushButton* saveButton;

    Mission* mission;
    QList<Item*> itemList;
public slots:
    void onHandButtonClicked();
    void onBeltButtonClicked();
    void onTrashButtonClicked();
    void onMinerButtonClicked();
    void onCutterButtonClicked();
    void onComposteButtonClicked();
    void onStoreButtonClicked();
    void onSaveButtonClicked();
    void removeToolContainerItem();
};


#endif // MAP_H
