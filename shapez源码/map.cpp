// map.cpp

#include "map.h"
#include"Val.h"
#include"mainwindow.h"
#include"item.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QGraphicsProxyWidget>
#include <iostream>
#include <fstream>
#include <QDir>
#include <QTextStream>
#include <QFile>

Map::Map(int rows, int columns, int tileSize, MainWindow* mw,QWidget *parent)
    : QWidget(parent), rows(rows), cols(columns), sz(tileSize), scene(new QGraphicsScene(this)),
    ToolContainerItem(nullptr),mainwindow(mw)
{
    tiles.resize(rows);
    for (int i = 0; i < rows; ++i) {
        tiles[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            tiles[i][j] = new Tile(this, i, j);
            tiles[i][j]->setSize(TileSize);
            tiles[i][j]->setMap(this);
            tiles[i][j]->setPixmap(QPixmap(":/image/image/tile.png"));
            scene->addItem(tiles[i][j]);
        }
    }
    toolArea = new QGraphicsRectItem(cols * tileSize, 0, ToolAreaWidth, rows * tileSize);
    toolArea->setBrush(QBrush(Qt::white));  // 设置矩形的背景颜色
    toolArea->setOpacity(0.1);  // 设置透明度为0，表示完全透明
    scene->addItem(toolArea);
    Buttons.resize(10);
    addButtons();
    addTradeCenter();
    setFocus();
    addOre();
    addMoneyAndCoin(1,0);
    addMission(1);
    qDebug()<<"Successfully create a map";


    globalCoin = 0;
    MoveSpeed = 1000;
    DigRate = 1.00;
    CutterRate = 1.00;

}

Map::Map(int rows, int columns, int tileSize, MainWindow *mw, const QString FilePath, QWidget *parent)
    : QWidget(parent), rows(rows), cols(columns), sz(tileSize), scene(new QGraphicsScene(this)),
    ToolContainerItem(nullptr),mainwindow(mw)
{

    tiles.resize(rows);
    for (int i = 0; i < rows; ++i) {
        tiles[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            tiles[i][j] = new Tile(this, i, j);
            tiles[i][j]->setSize(TileSize);
            tiles[i][j]->setMap(this);
            tiles[i][j]->setPixmap(QPixmap(":/image/image/tile.png"));
            scene->addItem(tiles[i][j]);
        }
    }

    toolArea = new QGraphicsRectItem(cols * tileSize, 0, ToolAreaWidth, rows * tileSize);
    toolArea->setBrush(QBrush(Qt::white));  // 设置矩形的背景颜色
    toolArea->setOpacity(0.1);  // 设置透明度为0，表示完全透明
    scene->addItem(toolArea);
    Buttons.resize(10);
    addButtons();
    addTradeCenter();
    addMission(0);

    setFocus();
    qDebug()<<"start load";
    int readMode = 0;
    int val = 0;
    QString filePath = "Save.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "unable to open the file:" << filePath;
        return;
    }

    int t1,t2,t3;
    QTextStream in(&file);
    QString word;
    while(readMode<6)
    {
        in >> word;
        if(word == "Inf"||word == "Mission" ||word == "Tile"|| word == "Facility"||word == "Item"||word == "end")
        {
            readMode++;
            continue;
        }
        switch(readMode)
        {
        case 1:
            val =fmax(val,word.toInt());
            in>>t1>>t2>>t3;
            // qDebug()<<word.toInt()<<t1<<t2<<t3;
            MoveSpeed =fmax(t1,1000);
            DigRate = fmax(t2,0.50);
            CutterRate = fmax(t3,0.50);
            break;
        case 2:
            in>>t1>>t2>>t3;
            // qDebug()<<word.toInt()<<t1<<t2<<t3;
            mission->updateItem(word.toInt(),t1,t2,t3);
            break;
        case 3:
            t1 = word.toInt();
            in>>t2>>t3;
            if(tiles[t2][t3]->isTradeCenter())
                continue;
            switch(t1){
            case 1:
                scene->removeItem(tiles[t2][t3]);
                tiles[t2][t3] = new IronOre(this, t2, t3);
                tiles[t2][t3]->setMap(this);
                scene->addItem(tiles[t2][t3]);
                break;
            case 2:
                scene->removeItem(tiles[t2][t3]);
                tiles[t2][t3] = new DiamondOre(this, t2, t3);
                tiles[t2][t3]->setMap(this);
                scene->addItem(tiles[t2][t3]);
                break;
            case 3:
                scene->removeItem(tiles[t2][t3]);
                tiles[t2][t3] = new NetheriteOre(this, t2, t3);
                tiles[t2][t3]->setMap(this);
                scene->addItem(tiles[t2][t3]);
                break;
            default:
                break;
            }
            break;
        case 4:
            in >> t1>>t2>>t3;
            // qDebug()<<word.toInt()<<t1<<t2<<t3;
            addFacility(tiles[t2][t3], word.toInt(),t1);
            break;
        case 5:

            in>>t1>>t2;
            if(tiles[t1][t2]->isTradeCenter()||!tiles[t1][t2]->facility)
                continue;
            Item* item;
            switch(word.toInt()){
            case 1:
                item = new Iron(tiles[t1][t2],scene);
                break;
            case 2:
                item = new Diamond(tiles[t1][t2],scene);
                break;
            case 3:
                item = new Netherite(tiles[t1][t2],scene);
                break;
            case 4:
                item = new IronPiece(tiles[t1][t2],scene);
                break;
            case 5:
                item = new Shit(tiles[t1][t2],scene);
                break;
            default:
                break;
            }
            if(tiles[t1][t2]->facility->getType()==3&&word.toInt() <=3)
                item->start();
            break;

        default:
            break;
        }
    }
    addMoneyAndCoin(0,val);
    globalMoney = val;
    coinVal = val;
}

Map::~Map()
{
    qDebug()<<"Start ~Map";
    while (!itemList.isEmpty()) {
        Item* i = itemList.takeFirst();
        delete i;
        i= nullptr;
    }

    itemList.clear();
    // qDebug()<<"!!!";

    itemList.clear();
    delete mission;

    delete tradeCenter;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(tiles[i][j])
            {
                delete tiles[i][j];
                tiles[i][j] =nullptr;
            }
            else{
                qDebug()<<"tile"<<i<<j<<"not exist";
            }
        }
    }
    removeToolContainerItem();
    delete ToolContainer;
    scene->clear();
    delete scene;
    qDebug()<<"end ~Map";


}

void Map::test()
{
}

void Map::test(Tile *tile)
{
    qDebug() << "Testing clicked tile:";
    qDebug() << "Tile at (" << tile->getIdX() << ", " << tile->getIdY() << ")";
    qDebug()<<"Tile id:"<<tile->getId();
    if (tile->getType()>=0)
    {
        qDebug() << "Facility Type: " << tile->getType();
        if(tile->hasFacility())
        {
            qDebug() << "Rotate Level: " << tile->facility->getRL();
            Tile* neibour = tile->getTileNeibour(tile->facility->getRL());
            if(neibour)
            {
                qDebug()<< "neibour pos:"<<neibour->getIdX()<<neibour->getIdY();
                qDebug() << "neibour Type:" << neibour->getType();
            }
        }
    }
}

void Map::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QRect rect(j * sz, i * sz, sz, sz);
            QPixmap pixmap = tiles[i][j]->getPixmap();
            painter.drawPixmap(rect, pixmap);
        }
    }
}

void Map::addItem(Item *item)
{
    if (item)
    {
        itemList.append(item);
    }
}

void Map::removeItem(Item *item)
{
    if (item&&!itemList.empty())
    {
        itemList.removeAll(item);
    }
}

Tile *Map::getTileFromPoint(QPoint point)
{
    int row = point.y() / sz; // sz 为 Tile 的大小
    int col = point.x() / sz;

    if ((row >= 0 && row < rows) && (col >= 0 && col < cols)) {
        return tiles[col][row];
    }
    return nullptr;
}

Tile* Map::getTileNeibour(Tile *tile, int direction)
{
    int dx[] = {0, 1, 0, -1};  // 方向数组，分别表示向上、向右、向下、向左
    int dy[] = {-1, 0, 1, 0};

    int x = tile->getIdX() + dx[direction % 4];
    int y = tile->getIdY() + dy[direction % 4];

    if (x < 0 || y < 0 || x >= cols || y >= rows)
        return nullptr;

    return tiles[x][y];
}
TradeCenter *Map::getTradeCenter() const{return tradeCenter;}
Mission *Map::getMission() const{return mission;}
Tile *Map::getTileFriend(Tile *tile, int direction)
{
    int dx[] = {1, 0, -1, 0};  // 方向数组，分别表示向上、向右、向下、向左
    int dy[] = {0, 1, 0, -1};

    int x = tile->getIdX() + dx[direction % 4];
    int y = tile->getIdY() + dy[direction % 4];

    if (x < 0 || y < 0 || x >= cols || y >= rows)
        return nullptr;

    return tiles[x][y];
}


void Map::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
    {
        rotateToolContainer();
    }
    if(event->key() == Qt::Key_T)
    {
        test();
    }
}

void Map::mousePressEvent(QMouseEvent *event) {


    if (event->button() == Qt::LeftButton||event->button() == Qt::RightButton||event->button() == Qt::ForwardButton) {
        // 获取鼠标在窗口中的坐标
        QPoint MousePos = event->pos();
        QPoint bias = QPoint(320,100);
        //获取不同窗口类导致的偏移量
        QPoint NewMousePos = MousePos -bias;
        // 判断是否在有效区域内
        if (NewMousePos.x() < 0 || NewMousePos.x() >= TileSize * cols || NewMousePos.y() < 0 || NewMousePos.y() >= TileSize * rows) {
            return;
        }

        // 获取点击到的 Tile
        Tile* clickedTile = getTileFromPoint(NewMousePos);
        //qDebug() << "Click tile at" << clickedTile->getIdX() << clickedTile->getIdY();
        if (clickedTile) {
            // 点击到 Tile 上的处理逻辑
            if(event->button() == Qt::LeftButton)
            {
                addFacility(clickedTile, ChosenId,rotatelevel);
                test(clickedTile);
            }

            if(event->button() == Qt::RightButton)
            {
                clickedTile->removefacility();
            }
            if(event->button() == Qt::ForwardButton)
            {
                test(clickedTile);
            }
        }
    }
}
void Map::addTradeCenter()
{
    int tempX = (rows-1) / 2, tempY = (cols-1) / 2;
    tradeCenter = new TradeCenter(tempX, tempY, this);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tiles[tempX + i][tempY + j]->filled();
            tiles[tempX + i][tempY + j]->setType(0);
        }
    }
    scene->addItem(tradeCenter);
    tradeCenter->setMap(this);
}

void Map::addOre()
{
    int ironGoal = QRandomGenerator::global()->bounded(IRONMIN, IRONMAX + 1);
    int diamondGoal = QRandomGenerator::global()->bounded(DIAMONDMIN, DIAMONDMAX + 1);
    int NetheriteGoal = QRandomGenerator::global()->bounded(NETHERITEMIN, NETHERITEMAX + 1);

    for (int k = 0; k < ironGoal; ) {
        int randX, randY;
        do {
            randX = QRandomGenerator::global()->bounded(0, rows);
            randY = QRandomGenerator::global()->bounded(0, cols);
        } while (!tiles[randX][randY]->empty());
        k++;
        scene->removeItem(tiles[randX][randY]);
        tiles[randX][randY] = new IronOre(this, randX, randY);
        tiles[randX][randY]->setMap(this);
        scene->addItem(tiles[randX][randY]);
    }
    for (int k = 0; k < diamondGoal; ) {
        int randX, randY;
        do {
            randX = QRandomGenerator::global()->bounded(0, rows);
            randY = QRandomGenerator::global()->bounded(0, cols);
        } while (!tiles[randX][randY]->empty());
        k++;
        scene->removeItem(tiles[randX][randY]);
        tiles[randX][randY] = new DiamondOre(this, randX, randY);
        tiles[randX][randY]->setMap(this);
        scene->addItem(tiles[randX][randY]);
    }
    for (int k = 0; k < NetheriteGoal; ) {
        int randX, randY;
        do {
            randX = QRandomGenerator::global()->bounded(0, rows);
            randY = QRandomGenerator::global()->bounded(0, cols);
        } while (!(tiles[randX][randY]->empty() && (randX < rows / 4 || randX >= rows * 3 / 4) && (randY < cols / 4 || randY >= cols * 3 / 4)));
        k++;
        scene->removeItem(tiles[randX][randY]);
        tiles[randX][randY] = new NetheriteOre(this, randX, randY);
        tiles[randX][randY]->setMap(this);
        scene->addItem(tiles[randX][randY]);
    }
}


void Map::addButtons()
{
    int ToolinitX = sz * cols;
    int ToolinitY = 0;
    int ToolBottom = sz * rows;
    Buttons.reserve(6);
    QPushButton* handButton = new QPushButton();
    handButton->setFixedSize(128, 128);
    QPixmap handPixmap(":/image/image/hand.png");
    handButton->setIcon(QIcon(handPixmap));
    handButton->setIconSize(handPixmap.size());
    scene->addWidget(handButton)->setPos(ToolinitX, ToolinitY);
    Buttons[0] = handButton;

    QPushButton* beltButton = new QPushButton();
    beltButton->setFixedSize(128, 128);
    QPixmap beltPixmap(":/image/image/belt.png");
    beltButton->setIcon(QIcon(beltPixmap));
    beltButton->setIconSize(beltPixmap.size());
    scene->addWidget(beltButton)->setPos(ToolinitX + 128, ToolinitY);
    Buttons[1] = beltButton;

    QPushButton* trashButton = new QPushButton();
    trashButton->setFixedSize(128, 128);
    QPixmap trashPixmap(":/image/image/trash.png");
    trashButton->setIcon(QIcon(trashPixmap));
    trashButton->setIconSize(trashPixmap.size());
    scene->addWidget(trashButton)->setPos(ToolinitX, ToolinitY + 128);
    Buttons[2] = trashButton;

    QPushButton* minerButton = new QPushButton();
    minerButton->setFixedSize(128, 128);
    QPixmap minerPixmap(":/image/image/miner.png");
    minerButton->setIcon(QIcon(minerPixmap));
    minerButton->setIconSize(minerPixmap.size());
    scene->addWidget(minerButton)->setPos(ToolinitX + 128, ToolinitY + 128);
    Buttons[3] = minerButton;

    QPushButton* cutterButton = new QPushButton();
    cutterButton->setFixedSize(256, 128);
    QPixmap cutterPixmap(":/image/image/cutter.png");
    cutterButton->setIcon(QIcon(cutterPixmap));
    cutterButton->setIconSize(cutterPixmap.size());
    scene->addWidget(cutterButton)->setPos(ToolinitX, ToolinitY + 256);
    Buttons[4] = cutterButton;

    QPushButton* ComposterButton = new QPushButton();
    ComposterButton->setFixedSize(128, 128);
    QPixmap ComposterPixmap(":/image/image/Composter_0.png");
    ComposterButton->setIcon(QIcon(ComposterPixmap));
    ComposterButton->setIconSize(ComposterPixmap.size());
    scene->addWidget(ComposterButton)->setPos(ToolinitX, ToolinitY+128*3);
    Buttons[5] = ComposterButton;

    QPushButton* StoreButton = new QPushButton();
    StoreButton->setFixedSize(128, 128);
    QPixmap StorePixmap(":/image/image/store.png");
    StoreButton->setIcon(QIcon(StorePixmap));
    StoreButton->setIconSize(StorePixmap.size());
    scene->addWidget(StoreButton)->setPos(ToolinitX+128, ToolinitY+128*3);
    Buttons[6] = StoreButton;

    QPixmap ToolContainerText(":/image/image/CurrentBottom.png");
    QGraphicsPixmapItem* ToolContainerTextItem = scene->addPixmap(ToolContainerText);
    ToolContainerTextItem->setPos(ToolinitX, ToolBottom - 128);
    ToolContainer = new QPixmap(":/image/image/initContainer.png");
    ToolContainerItem = scene->addPixmap(*ToolContainer);
    ToolContainerItem->setPos(ToolinitX + 128, ToolBottom - 128);
    ChosenId = 0;
    rotatelevel = 0;


    connect(Buttons[0], &QPushButton::clicked, this, &Map::onHandButtonClicked);
    connect(Buttons[1], &QPushButton::clicked, this, &Map::onBeltButtonClicked);
    connect(Buttons[2], &QPushButton::clicked, this, &Map::onTrashButtonClicked);
    connect(Buttons[3], &QPushButton::clicked, this, &Map::onMinerButtonClicked);
    connect(Buttons[4], &QPushButton::clicked, this, &Map::onCutterButtonClicked);
    connect(Buttons[5], &QPushButton::clicked, this, &Map::onComposteButtonClicked);
    connect(Buttons[6], &QPushButton::clicked, this, &Map::onStoreButtonClicked);


    saveButton = new QPushButton("Save&&Exit");
    saveButton->setFixedSize(256,64);
    saveButton->setFont(QFont("Arial", 18, QFont::Bold));
    saveButton->setGeometry(sz * cols, 128*7,256,64);
    if (scene)
    {
        scene->addWidget(saveButton);
    }
    connect(saveButton,&QPushButton::clicked, this, &Map::onSaveButtonClicked);
}
/*
   facilityType(chosenId):facility
    -1:emptyTile
    0:TradeCenter
    1:belt
    2:miner
    3:trash
    4:cutter
    5:Composter
    6:cutter2
*/
void Map::addFacility(Tile *tile, int facilityType,int rl)
{
    if(tile->hasFacility()||tile->isTradeCenter())
    {
        return;
    }
    switch (facilityType) {
    case 1: //传送带
        tile->facility = new Belt(tile,scene,rl);
        scene->addItem(tile->facility);
        break;
    case 2://垃圾桶
        tile->facility = new Trash(tile,scene,rl);
        scene->addItem(tile->facility);
        break;
    case 3://采矿机
        tile->facility = new Miner(tile,scene,rl);
        scene->addItem(tile->facility);
        break;

    case 5:
        tile->facility = new Composter(tile,scene,rl);
        scene->addItem(tile->facility);
        break;
    default:
        break;
    }
    if(facilityType == 4) //切割机
    {
        Tile* tile2 = getTileFriend(tile,rl);
        if(!tile2||tile2->hasFacility()||tile2->isTradeCenter()){
            qDebug()<<"fail to add Cutter";
            return;
        }
        Cutter* c = new Cutter(tile,scene,rl);
        tile->facility = c;
        scene->addItem(tile->facility);
        Cutter2* c2 = new Cutter2(tile2,scene,rl);
        c->setC2(c2);
        tile2->facility = c2;
        scene->addItem(tile2->facility);
    }
}
void Map::addMoneyAndCoin(bool init,int val)
{
    //硬币
    QPixmap coinPixmap(":/image/image/coin.png");
    QGraphicsPixmapItem* coinItem = scene->addPixmap(coinPixmap.scaled(64, 64));
    coinItem->setPos(sz * cols, 128*4);
    //硬币数值
    QString coinInit;
    if(init)
        coinInit = "0";
    else
        coinInit = QString::number(val);
    coinValueItem = new QGraphicsTextItem(coinInit);  // 初始化数值为0
    coinVal = globalCoin;
    coinValueItem->setPos(sz * cols + 64, 128*4);
    coinValueItem->setFont(QFont("Arial", 24, QFont::Bold));
    coinValueItem->setDefaultTextColor(Qt::white);
    scene->addItem(coinValueItem);
    //绿宝石
    QPixmap moneyPixmap(":/image/image/money.png");
    QGraphicsPixmapItem* moneyItem = scene->addPixmap(moneyPixmap.scaled(64, 64));
    moneyItem->setPos(sz * cols, 128*4+64);
    //绿宝石数值
    moneyValueItem = new QGraphicsTextItem(QString::number(globalMoney));  // 初始化数值
    moneyVal = globalMoney;
    moneyValueItem->setPos(sz * cols + 64, 128*4+64);
    moneyValueItem->setFont(QFont("Arial", 24, QFont::Bold));
    moneyValueItem->setDefaultTextColor(Qt::white);
    scene->addItem(moneyValueItem);
}

void Map::addMission(bool init)
{
    mission = new Mission(init,this,scene);
    QGraphicsTextItem* text1 = new QGraphicsTextItem("Mission ");
    text1->setPos(sz * cols, 128*5);
    text1->setFont(QFont("Arial", 18, QFont::Bold));
    text1->setDefaultTextColor(Qt::white);
    scene->addItem(text1);

    QGraphicsTextItem* text2 = new QGraphicsTextItem("Type:");
    text2->setPos(sz * cols, 128*5+64);
    text2->setFont(QFont("Arial", 18, QFont::Bold));
    text2->setDefaultTextColor(Qt::white);
    scene->addItem(text2);

    QGraphicsTextItem* text3 = new QGraphicsTextItem("Current:");
    text3->setPos(sz * cols, 128*6);
    text3->setFont(QFont("Arial", 18, QFont::Bold));
    text3->setDefaultTextColor(Qt::white);
    scene->addItem(text3);

    QGraphicsTextItem* text4 = new QGraphicsTextItem("Target:");
    text4->setPos(sz * cols, 128*6+64);
    text4->setFont(QFont("Arial", 18, QFont::Bold));
    text4->setDefaultTextColor(Qt::white);
    scene->addItem(text4);
}


void Map::setMainWindow(MainWindow *mw)
{
    mainwindow = mw;
}


void Map::rotateToolContainer()
{
    if (ToolContainerItem&&ChosenId>0) {
        QTransform rotationTransform;
        rotationTransform.rotate(90);  // 逆时针旋转 90 度
        // 使用transformed函数获得旋转后的QPixmap
        QPixmap rotatedPixmap = ToolContainer->transformed(rotationTransform);
        // 更新ToolContainer成员变量
        *ToolContainer = rotatedPixmap;
        // 更新ToolContainerItem的Pixmap
        ToolContainerItem->setPixmap(rotatedPixmap);
        rotatelevel =(rotatelevel+1)%4;
    }
}

void Map::addCoin(int num)
{
    if(num+coinVal>=0)
    {
        // qDebug()<<"add coin:"<<num;
        coinVal+=num;
        globalCoin = coinVal;
        coinValueItem->setPlainText(QString::number(coinVal));
    }
    else{
        coinVal=0;
        globalCoin = coinVal;
        coinValueItem->setPlainText(QString::number(coinVal));
    }
}

void Map::addMoney(int num)
{
    if(num+moneyVal>=0)
    {
        moneyVal+=num;
        globalMoney=moneyVal;
        moneyValueItem->setPlainText(QString::number(moneyVal));
    }
    else{
        moneyVal=0;
        globalMoney=moneyVal;
        moneyValueItem->setPlainText(QString::number(moneyVal));
    }
}

void Map::onHandButtonClicked()
{
    removeToolContainerItem();
    qDebug() << "Hand button clicked!";
    ChosenId = 0;
    ToolContainer = new QPixmap(":/image/image/hand.png");
    ToolContainerItem = scene->addPixmap(*ToolContainer);
    ToolContainerItem->setPos(sz * cols + 128, sz * rows - 128);
}

void Map::onBeltButtonClicked()
{
    removeToolContainerItem();
    qDebug() << "Belt button clicked!";
    ChosenId = 1;
    rotatelevel = 0;
    ToolContainer = new QPixmap(":/image/image/belt.png");
    ToolContainerItem = scene->addPixmap(*ToolContainer);
    ToolContainerItem->setPos(sz * cols + 128, sz * rows - 128);
}

void Map::onTrashButtonClicked()
{
    removeToolContainerItem();
    qDebug() << "Trash button clicked!";
    ChosenId = 2;
    rotatelevel = 0;
    ToolContainer = new QPixmap(":/image/image/trash.png");
    ToolContainerItem = scene->addPixmap(*ToolContainer);
    ToolContainerItem->setPos(sz * cols + 128, sz * rows - 128);
}

void Map::onMinerButtonClicked()
{
    removeToolContainerItem();
    qDebug() << "Miner button clicked!";
    ChosenId = 3;
    rotatelevel = 0;
    ToolContainer = new QPixmap(":/image/image/miner.png");
    ToolContainerItem = scene->addPixmap(*ToolContainer);
    ToolContainerItem->setPos(sz * cols + 128, sz * rows - 128);
}

void Map::onCutterButtonClicked()
{
    removeToolContainerItem();
    qDebug() << "Cutter button clicked!";
    ChosenId = 4;
    rotatelevel = 0;

    ToolContainer = new QPixmap(":/image/image/cutterSmall.png");
    ToolContainerItem = scene->addPixmap(*ToolContainer);
    ToolContainerItem->setPos(sz * cols + 128, sz * rows - 128);
}
void Map::onComposteButtonClicked()
{
    removeToolContainerItem();
    qDebug() << "Composte button clicked!";
    ChosenId = 5;
    rotatelevel = 0;

    ToolContainer = new QPixmap(":/image/image/Composter_0.png");
    ToolContainerItem = scene->addPixmap(*ToolContainer);
    ToolContainerItem->setPos(sz * cols + 128, sz * rows - 128);
}

void Map::onStoreButtonClicked()
{
    mainwindow->hide();
    mainwindow->store->show();
}

void Map::onSaveButtonClicked() // 存档
{
    QString filePath = "Save.txt";
    std::ofstream out(filePath.toStdString(), std::ios::out | std::ios::trunc);
    if (!out.is_open()) // 未打开即报错
    {
        std::cerr << "Error: Unable to open the file for saving." << std::endl;
        return;
    }
    out<<"Inf"<<std::endl;
    out<<globalCoin<<" "<<MoveSpeed<<" "<<DigRate<<" "<<CutterRate<<std::endl;
    out << "Mission" << std::endl;
    out << mission->getID() << " " << mission->getTarget() << " " << mission->getCur() << " " << mission->getItemID() << std::endl;
    out << "Tile" << std::endl;
    for(int i=0;i<MapHeight;i++)
    {
        for(int j=0; j<MapWidth;j++)
        {
            if(tiles[i][j]->getId()>0&&!tiles[i][j]->isTradeCenter())
            {
                out<<tiles[i][j]->getId()<<" "<<i<<" "<<j<<std::endl;
            }
        }
    }
    out << "Facility" << std::endl;
    for(int i=0;i<MapHeight;i++)
    {
        for(int j=0; j<MapWidth;j++)
        {
            if(tiles[i][j]->hasFacility()){
                Facility* f = tiles[i][j] ->facility;
                if(f->getType()==6)
                    continue;
                else {
                    out<<f->getType()<<" "<<f->getRL()<<" "<<i<<" "<<j<<std::endl;
                }
            }
        }
    }
    out << "Item" << std::endl;
    for (QList<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
    {
        if(*it)
        {
            Item* item = *it;
            out<<item->getId()<<" "<<item->getIdX()<<" "<<item->getIdY()<<std::endl;
        }
    }
    out<<"end";
    // 结束, 窗口切换
    out.close();
    mainwindow->showMenu();
    mainwindow->hide();

    qDebug()<<"Finish saving";

}

QGraphicsScene* Map::getScene() const{return scene;}
int Map::getRows() const{return rows;}
int Map::getCols() const{return cols;}
Tile* Map::getTile(int row, int col) const{
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return tiles[row][col];
    }
    return nullptr;
}
void Map::removeToolContainerItem()
{
    if (ToolContainerItem) {
        scene->removeItem(ToolContainerItem);
        delete ToolContainerItem;
        ToolContainerItem = nullptr;
    }
}

