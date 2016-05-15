#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QFileDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Data Utility");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    w.show();
    return a.exec();
}
