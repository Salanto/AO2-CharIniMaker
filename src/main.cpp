#include "ao2charmaker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    AO2CharMaker ui_window;
    ui_window.show();
    return App.exec();
}
