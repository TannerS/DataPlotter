#include "graph.h"

// get time stamp (this is as a string from file)
std::string Graph::getTime()
{
    return this->time;
}
// set time (as string from file)
void Graph::setTime(std::string time)
{
    this->time = time;
}
// set file name
void Graph::setFileName(QString name)
{
    this->file_name = name;
}
// get file name
QString Graph::getFileName()
{
    return this->file_name;
}
// set a single x axis
void Graph::setXAxisVectorPoint(double x)
{
    this->x.push_back(x);
}
// set a single y axis
void Graph::setYAxisVectorPoint(double y)
{
    this->y.push_back(y);
}
// get x vector
QVector<double> Graph::getXAxisVector()
{
    return this->x;
}
// get y vector
QVector<double> Graph::getYAxisVector()
{
    return this->y;
}
// set x min value
void Graph::setXMin(float min)
{
    this->xmin = min;
}
// set x max value
void Graph::setXMax(float max)
{
    this->xmax = max;
}
// set y min value
void Graph::setYMin(float min)
{
    this->ymin = min;
}
// set y max value
void Graph::setYMax(float max)
{
    this->ymax = max;
}
// get x min value
float Graph::getXMin()
{
    return this->xmin;
}
// get x max value
float Graph::getXMax()
{
    return this->xmax;
}
// get y min value
float Graph::getYMin()
{
    return this->ymin;
}
// get y max value
float Graph::getYMax()
{
    return this->ymax;
}
// get file path
QString Graph::getPath()
{
    return this->path;
}
// set file path
void Graph::setPath(QString path)
{
    this->path = path;
}

