//mainwindow.cpp
#include "mainwindow.h"
#include "menu.h"
#include "./ui_mainwindow.h"
#include <QGraphicsView>
#include <QDesktopWidget>
#include"Val.h"
MainWindow::MainWindow(Menu* MENU,int reload,QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),gameMap(nullptr),menu(MENU)
{
    qDebug()<<"Create a mainwindow";
    ui->setupUi(this);
    setWindowTitle("Shapez");
    setFixedSize(WindowWidth, WindowHeight);

    // 创建地图
    if(reload)
    {
        gameMap = new Map(MapWidth, MapHeight, TileSize, this,":/image/image/tile.png");
    }
    else
    {
        gameMap = new Map(MapWidth, MapHeight, TileSize, this);
    }
    store = new Store(this);
    store->hide();
    // 创建 QGraphicsView，并设置其场景
    QGraphicsView* view = new QGraphicsView(gameMap->getScene(), this);
    // 设置 QGraphicsView 为中央部件
    setCentralWidget(view);
    // 移动视图到中心
    moveToCenter();
}

MainWindow::~MainWindow()
{
    // qDebug()<<"start ~MainWindow";
    if(ui)
        delete ui;
    if(gameMap)
    {
        delete gameMap;
        gameMap = nullptr;
    }
    delete store;
    // qDebug()<<"end ~MainWindow";
}

void MainWindow::moveToCenter()
{
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    // qDebug()<<screenWidth<<screenHeight;
    // 计算窗口居中的坐标
    int x = (screenWidth - width()) / 2;
    int y = (screenHeight - height()) / 2-50;

    // 移动窗口到计算出的坐标
    move(x, y);
    qDebug()<<"Window moved:"<<x<<y;
}

void MainWindow::keyPressEvent(QKeyEvent *keyevent)
{
    gameMap->keyPressEvent(keyevent);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    gameMap->mousePressEvent(event);
}


Menu *MainWindow::getMenu() const
{
    return menu;
}

void MainWindow::showMenu()
{
    qDebug()<<"global money"<<globalMoney;
    menu->resetMenuInit(globalMoney,1);
    menu->show();
}

