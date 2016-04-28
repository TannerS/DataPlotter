#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filedata.h"
#include "filenames.h"
#include "fileparser.h"
#include "grapher.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void test();

private slots:
    void on_select_files_clicked();
    void on_plot_files_clicked();

private:
    Ui::MainWindow *ui;
    void initFiles(QStringList);
    void renameFiles();
    FileData* data;
    FileNames* names;
    FileParser* parser;
    void ParseFiles();
    Grapher* grapher;
    void generateGraphs();
};

#endif // MAINWINDOW_H
