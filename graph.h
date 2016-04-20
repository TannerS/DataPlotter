#ifndef GRAPHS_H
#define GRAPHS_H
#include <QString>
#include <QVector>

class Graph
{
    public:
        Graph();
        QString getPath();
        void setPath(QString);
        void setFileName(QString);
        QString getFileName();
        void setXAxisVector(QVector<double>);
        void setYAxisVector(QVector<double>);
        QVector<double> getXAxisVector();
        QVector<double> getYAxisVector();
        void setXMin(float);
        void setXMax(float);
        void setYMin(float);
        void setYMax(float);
        float getXMin();
        float getXMax();
        float getYMin();
        float getYMax();

    private:
        QString file_name;// = QString::fromStdString(name);
        QString path;
        QVector<double> x;
        QVector<double> y;
        float xmin;
        float xmax;
        float ymin;
        float ymax;
};

#endif // GRAPHS_H
