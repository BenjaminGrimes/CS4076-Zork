#include "mainwindow.h"
#include "startmenuwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Show start menu window
    StartMenuWindow sw;
    sw.setWindowTitle("Zork - Start Menu");
    sw.show();

    /*
    MainWindow w;
    w.setWindowTitle("Zork");
    w.showMaximized();*/
    //w.show();

    return a.exec();
}
