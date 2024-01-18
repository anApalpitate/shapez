#include "globalstore.h"
#include "ui_globalstore.h"
#include "Val.h"
#include "menu.h"
#include <QPushButton>
GlobalStore::GlobalStore(Menu *menu, QWidget *parent)
    : QWidget(parent), ui(new Ui::GlobalStore), menu(menu)
{
    ui->setupUi(this);
    setWindowTitle("GlobalStore owned by a villager");
    setWindowIcon(QIcon(":/image/image/villager.png"));

    setFixedSize(960, 600);
    initMoney();
    connect(ui->exitButton, &QPushButton::clicked, this, &GlobalStore::onExitClicked);
    connect(ui->b1, &QPushButton::clicked, this, &GlobalStore::onB1clicked);
    connect(ui->b2, &QPushButton::clicked, this, &GlobalStore::onB2clicked);
    connect(ui->b3, &QPushButton::clicked, this, &GlobalStore::onB3clicked);
    QVector<int> v = menu->ReadMenuInit();
    if (v[0] < 0)
        exit(-1);
    b1 = v[1];
    b2 = v[2];
    b3 = v[3];
    if (b1)
        ui->b1->setText("Acquired");
    if (b2)
        ui->b2->setText("Acquired");
    if (b3)
        ui->b3->setText("Acquired");

}
void GlobalStore::initMoney()
{
    money = globalMoney;
    ui->money->setText(QString::number(money));
    ui->money->setFont(QFont("Arial", 18));
    ui->money->setAlignment(Qt::AlignCenter);
}
GlobalStore::~GlobalStore()
{
    delete ui;
}

void GlobalStore::onExitClicked()
{
    if (b1)
        ui->b1->setText("Acquired");
    if (b2)
        ui->b2->setText("Acquired");
    if (b3)
        ui->b3->setText("Acquired");
    menu->resetMenuInit(money, b1, b2, b3);
    hide();
    menu->show();
    globalMoney = money;
}

void GlobalStore::onB1clicked()
{
    if (b1 || money < 100)
        return;
    money -= 100;
    ui->money->setText(QString::number(money));
    b1 = 1;
    ui->b1->setText("Acquired");
}

void GlobalStore::onB2clicked()
{
    if (b2 || money < 75)
        return;
    money -= 75;
    ui->money->setText(QString::number(money));
    ui->money->setFont(QFont("Arial", 18));
    ui->money->setAlignment(Qt::AlignCenter);
    b2 = 1;
    ui->b2->setText("Acquired");
}

void GlobalStore::onB3clicked()
{
    if (b3 || money < 50)
        return;
    money -= 50;
    ui->money->setText(QString::number(money));
    ui->money->setFont(QFont("Arial", 18));
    ui->money->setAlignment(Qt::AlignCenter);
    b3 = 1;
    ui->b3->setText("Acquired");
}


