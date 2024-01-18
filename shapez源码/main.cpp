#include "menu.h"

#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Menu menu ;
    menu.show();
    return a.exec();
}
