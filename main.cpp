#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QFileDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // set name of title
    w.setWindowTitle("Data Utility");
    // may not be needed, based of RES of monitor
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    w.show();
    return a.exec();
}
