#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filedata.h"

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

private slots:
    void on_select_dir_clicked();

private:
    Ui::MainWindow *ui;
    void initFiles(QStringList);
    FileData* data;
};

#endif // MAINWINDOW_H
