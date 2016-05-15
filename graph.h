#ifndef GRAPHS_H
#define GRAPHS_H
#include <QString>
#include <QVector>

class Graph
{
    public:
        QString getPath();
        void setPath(QString);
        void setFileName(QString);
        QString getFileName();
        void setXAxisVectorPoint(double);
        void setYAxisVectorPoint(double);
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
        std::string getTime();
        void setTime(std::string);

    private:
        QString file_name;
        QString path;
        QVector<double> x;
        QVector<double> y;
        float xmin;
        float xmax;
        float ymin;
        float ymax;
        std::string time;
};

#endif // GRAPHS_H
