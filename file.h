#ifndef FILE_H
#define FILE_H

#include "boost/filesystem/path.hpp"

class File
{
    public:
        boost::filesystem::path getPath();
        void setPath(boost::filesystem::path path);
        time_t getModifiedTime();
        void setModifiedTime(time_t time);

    private:
        boost::filesystem::path path;
        time_t last_modified_state;
};

#endif // FILE_H
