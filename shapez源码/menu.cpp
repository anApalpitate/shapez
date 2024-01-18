#include "menu.h"
#include "Val.h"
#include "ui_menu.h"
#include <fstream>
#include <iostream>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextStream>

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu),gameWindow(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Shapez");
    init();

    globalStore = new GlobalStore(this);
    connect(ui->MenuStartButton, &QPushButton::clicked, this,&Menu::onMenuStartButtonClicked);
    connect(ui->ReadPushButton,&QPushButton::clicked,this,&Menu::onReadButtonClicked);
    connect(ui->StorePushButton,&QPushButton::clicked,this,&Menu::onStoreButtonClicked);

    music = new QSoundEffect(this);
    music->setSource(QUrl::fromLocalFile(":/music/music/music.wav"));
    music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    music->setVolume(0.5f);  //设置音量
    music->play();
}

Menu::~Menu()
{
    delete ui;
    delete globalStore;
    if(gameWindow)
    {
        delete gameWindow;
        gameWindow = nullptr;
    }
}

void Menu::init()
{
    // QDir currentDir(QDir::currentPath());
    // qDebug() << "Working directory:" << currentDir.absolutePath();
    // qDebug() << "Files in current directory:";

    // // 获取文件列表
    // QStringList files = currentDir.entryList(QDir::Files);

    // // 输出文件名
    // for (const QString &file : files) {
    //     qDebug() << file;
    // }

    std::ifstream inputFile("menuInit.txt");  //如无法使用，建议改为绝对路径
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open menuInit.txt. Error: " << strerror(errno) << std::endl;
        return;
    }
    bool upgradeOre=0,upgradeCoin=0,upgradeShit=0;
    inputFile>>globalMoney>>upgradeOre>>upgradeCoin>>upgradeShit;
    inputFile.close();
    if(upgradeOre){
        DIAMONDMAX = 40;
        DIAMONDMIN = 30;
        IRONMAX = 80;
        IRONMIN = 40;
        NETHERITEMAX = 20 ;
        NETHERITEMIN = 5;
    }
    else{
        DIAMONDMAX = 30;
        DIAMONDMIN = 20;
        IRONMAX = 50;
        IRONMIN = 30;
        NETHERITEMAX = 10 ;
        NETHERITEMIN = 2;
    }
    if(upgradeCoin){
        CoinRate = 2;
    }
    else{
        CoinRate = 1;
    }
    if(upgradeShit)
    {
        ComposterRate = 10;
    }
    else{
        ComposterRate = 1 ;
    }
    inputFile.close();
}

void Menu::resetMenuInit(int num, int b1, int b2, int b3)
{
    QString filePath = "menuInit.txt";
    QFile file(filePath);

    // 打开文件，如果无法打开则输出错误信息并返回
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open menuInit.txt for writing.";
        return;
    }
    QTextStream out(&file);
    // 清空原文件内容
    file.resize(0);
    // 逐行写入四个变量
    out << num << "\n" << b1 << "\n" << b2 << "\n" << b3 << "\n";
    file.close();
}

QVector<int> Menu::ReadMenuInit()
{
    std::ifstream inputFile("menuInit.txt");  //如无法使用，建议改为绝对路径
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open menuInit.txt. Error: " << strerror(errno) << std::endl;
        return {-1};
    }
    int x;
    bool b1,b2,b3;
    inputFile>>x>>b1>>b2>>b3;
    return {x,b1,b2,b3};
}


void Menu::resetMenuInit(int num, int line)
{
    QString filePath = "menuInit.txt";

    // 打开文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Unable to open menuInit.txt.";
        return;
    }

    // 读取原始内容
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines << in.readLine();
    }
    // 关闭文件
    file.close();

    // 如果行数有效，则修改该行的内容
    if (line > 0 && line <= lines.size()) {
        lines[line - 1] = QString::number(num);
    } else {
        qDebug() << "Invalid line number.";
        return;
    }

    // 打开文件并写入修改后的内容
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < lines.size(); i++) {
            out << lines[i];
            // 判断是否是最后一行，如果不是则写入换行符
            if (i < lines.size() - 1) {
                out << '\n';
            }
        }
        // 关闭文件
        file.close();
    } else {
        qDebug() << "Unable to open menuInit.txt for writing.";
    }
}


void Menu::onMenuStartButtonClicked()
{
    // 隐藏当前 Menu
    gameWindow = new MainWindow(this,0);
    gameWindow->hide();
    hide();
    // 显示 MainWindow
    gameWindow->show();
}

void Menu::onStoreButtonClicked()
{
    hide();
    globalStore->initMoney();
    globalStore->show();
}

void Menu::onReadButtonClicked()
{
    qDebug() << "start of Menu::onReadButtonClicked";

    // 创建一个指向新gameWindow的临时指针
    MainWindow* newGameWindow = new MainWindow(this, 1);
    qDebug()<<"Successfully build the gameWindow";
    // 隐藏当前gameWindow
    if (gameWindow)
    {
        gameWindow->hide();
        delete gameWindow;  // 删除现有的gameWindow对象
    }

    // 只有在成功创建新对象时才更新gameWindow指针
    gameWindow = newGameWindow;

    // 隐藏当前Menu并显示新的gameWindow
    hide();
    gameWindow->show();

    qDebug() << "end of Menu::onReadButtonClicked";
}

