#include "file.h"

boost::filesystem::path File::getPath()
{
    return this->path;
}

void File::setPath(boost::filesystem::path path)
{
    this->path = path;
}

time_t File::getModifiedTime()
{
    return this->last_modified_state;
}

void File::setModifiedTime(time_t time)
{
    this->last_modified_state = time;
}

void File::addPath(File path)
{
   // this->paths.
}
