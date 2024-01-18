#include "store.h"
#include "ui_store.h"
#include "Val.h"
#include "mainwindow.h"

Store::Store(MainWindow *mw, QWidget *parent)
    : mainwindow(mw), QWidget(parent), ui(new Ui::store)
{
    ui->setupUi(this);
    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout, this, &Store::updateCoin);
    connect(updateTimer, &QTimer::timeout, this, &Store::updateIcon);
    updateTimer->start(1000);
    connect(ui->EXIT, &QPushButton::clicked, this, &Store::onExitClicked);
    connect(ui->B1, &QPushButton::clicked, this, &Store::buy1);
    connect(ui->B2, &QPushButton::clicked, this, &Store::buy2);
    connect(ui->B3, &QPushButton::clicked, this, &Store::buy3);

    setWindowTitle("Store owned by a villager");
    setWindowIcon(QIcon(":/image/image/villager.png"));
}

Store::~Store()
{
    delete ui;
    updateTimer->stop();
    delete updateTimer;
    updateTimer = nullptr;
}

void Store::onExitClicked()
{
    hide();
    mainwindow->show();
}

void Store::updateCoin()
{
    coin = globalCoin;
    ui->coin->setText(QString::number(coin));
}

void Store::updateIcon()
{
    if(MoveSpeed!=1000&&MoveSpeed!=900&&MoveSpeed!=700&&MoveSpeed!=500)
    {
        MoveSpeed = 1000;
    }
    if (DigRate != 1.00&&DigRate!=0.90&&DigRate!=0.70&&DigRate!=0.50)
    {
        DigRate = 1.00;
    }
    if (CutterRate != 1.00&&CutterRate!=0.90&&CutterRate!=0.70&&CutterRate!=0.50)
    {
        CutterRate = 1.00;
    }
    if (MoveSpeed == 1000)
    {
        ui->color11->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color12->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color13->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B1->setText("$" + QString::number(200));
    }
    else if (MoveSpeed == 900)
    {
        ui->color11->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color12->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color13->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B1->setText("$" + QString::number(500));
    }
    else if (MoveSpeed == 700)
    {
        ui->color11->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color12->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color13->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B1->setText("$" + QString::number(1000));
    }
    else if (MoveSpeed == 500)
    {
        ui->color11->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color12->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color13->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->B1->setText("Full level");
    }

    if (DigRate == 1.00)
    {
        ui->color21->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color22->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color23->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B2->setText("$" + QString::number(200));
    }
    else if (DigRate == 0.90)
    {
        ui->color21->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color22->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color23->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B2->setText("$" + QString::number(500));
    }
    else if (DigRate == 0.70)
    {
        ui->color21->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color22->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color23->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B2->setText("$" + QString::number(1000));
    }
    else if (DigRate == 0.50)
    {
        ui->color21->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color22->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color23->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->B2->setText("Full level");
    }

    if (CutterRate == 1.00)
    {
        ui->color31->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color32->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color33->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B3->setText("$" + QString::number(200));
    }
    else if (CutterRate == 0.90)
    {
        ui->color31->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color32->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->color33->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B3->setText("$" + QString::number(500));
    }
    else if (CutterRate == 0.70)
    {
        ui->color31->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color32->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color33->setPixmap(QPixmap(":/image/image/grey.png").scaled(128, 128));
        ui->B3->setText("$" + QString::number(1000));
    }
    else if (CutterRate == 0.50)
    {
        ui->color31->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color32->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->color33->setPixmap(QPixmap(":/image/image/green.png").scaled(128, 128));
        ui->B2->setText("Full level");
    }
}

void Store::buy1()
{
    if (MoveSpeed == 1000)
    {
        if (globalCoin > 200)
        {
            MoveSpeed = 900;
            globalCoin -= 200;
        }
    }
    else if (MoveSpeed == 900)
    {
        if (globalCoin > 500)
        {
            MoveSpeed = 700;
            globalCoin -= 500;
        }
    }
    else if (MoveSpeed == 700)
    {
        if (globalCoin > 1000)
        {
            MoveSpeed = 500;
            globalCoin -= 1000;
        }
    }
    updateCoin();
    updateIcon();
}

void Store::buy2()
{
    if (DigRate == 1.00)
    {
        if (globalCoin > 200)
        {
            DigRate = 0.90;
            globalCoin -= 200;
        }
    }
    else if (DigRate == 0.90)
    {
        if (globalCoin > 500)
        {
            DigRate = 0.70;
            globalCoin -= 500;
        }
    }
    else if (DigRate == 0.70)
    {
        if (globalCoin > 1000)
        {
            DigRate = 0.50;
            globalCoin -= 1000;
        }
    }
    updateCoin();
    updateIcon();
}

void Store::buy3()
{
    if (CutterRate == 1.00)
    {
        if (globalCoin > 200)
        {
            CutterRate = 0.90;
            globalCoin -= 200;
        }
    }
    else if (CutterRate == 0.90)
    {
        if (globalCoin > 500)
        {
            CutterRate = 0.70;
            globalCoin -= 500;
        }
    }
    else if (CutterRate == 0.70)
    {
        if (globalCoin > 1000)
        {
            CutterRate = 0.50;
            globalCoin -= 1000;
        }
    }
    updateCoin();
    updateIcon();
}
