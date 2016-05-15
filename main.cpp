#include "mainwindow.h"
#include <QApplication>

// main program
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // set name of title
    w.setWindowTitle("Data Utility");
    // may not be needed, based of RES of monitor
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // show application
    w.show();
    // return instance of application
    return a.exec();
}
