#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"map.h"
#include"store.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class Menu;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Menu* menu,int reload,QWidget *parent = nullptr);
    ~MainWindow();
    void moveToCenter();
    void keyPressEvent(QKeyEvent *keyevent) override;
    void mousePressEvent(QMouseEvent *event) override;
    Menu* getMenu()const;
    void showMenu();
    Store* store;
private:
    Ui::MainWindow *ui;
    Map* gameMap;
    Menu* menu;
};
#endif // MAINWINDOW_H
