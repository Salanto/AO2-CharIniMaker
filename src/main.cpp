#include "ao2charmaker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    App.setApplicationVersion("0.1");
    App.setApplicationName("AO2 Char.ini Editor v1");
    AO2CharMaker ui_window;
    ui_window.show();
    return App.exec();
}
