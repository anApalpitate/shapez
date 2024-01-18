#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include<QPushButton>
#include"mainwindow.h"
#include"globalstore.h"
namespace Ui {
class menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void init();
    void resetMenuInit(int num,int b1,int b2,int b3);
    QVector<int> ReadMenuInit();
    void resetMenuInit(int num,int line);
private:
    Ui::menu *ui;
    MainWindow *gameWindow;
    GlobalStore* globalStore;
    QSoundEffect *music;

private slots:
    void onMenuStartButtonClicked();
    void onStoreButtonClicked();
    void onReadButtonClicked();
};

#endif // MENU_H
