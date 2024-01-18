#ifndef GLOBALSTORE_H
#define GLOBALSTORE_H

#include <QWidget>
namespace Ui {
class GlobalStore;
}
class Menu;
class GlobalStore : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalStore(Menu* menu,QWidget *parent = nullptr);
    ~GlobalStore();
public slots:
    void onExitClicked();
    void onB1clicked();
    void onB2clicked();
    void onB3clicked();
    void initMoney();
private:
    bool b1;
    bool b2;
    bool b3;
    int money;
    Ui::GlobalStore *ui;
    Menu* menu;
};

#endif // GLOBALSTORE_H
