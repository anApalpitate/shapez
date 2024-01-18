#ifndef STORE_H
#define STORE_H

#include <QWidget>
#include<QTimer>
namespace Ui {
class store;
}
class MainWindow;
class Store : public QWidget
{
    Q_OBJECT

public:
    explicit Store(MainWindow* mw,QWidget *parent = nullptr);
    ~Store();
public slots:
    void onExitClicked();
private:
    void updateCoin();
    void updateIcon();
    void buy1();
    void buy2();
    void buy3();
    int coin;
    int level1,level2,level3;
    Ui::store *ui;
    MainWindow* mainwindow;
    QTimer* updateTimer;
};

#endif // STORE_H
