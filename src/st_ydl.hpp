/*
    Reads the file and creates for every (valid) link a "ydl_data" object and stores it in the vector "data"
*/

#ifndef __ST_YDL_HPP__
#define __ST_YDL_HPP__

#include <string>
#include <map>

using namespace std;

class YDLdata;

class STydl
{
public:
    STydl(string _file);
    ~STydl();

    // Returns the number of all Downloads to be executed.
    int get_all_downloads();

    // Downloads the i link.
    // void operator[](unsigned int i);

    void printProgress(bool firstRun);

    void download_multithreading(int _threads_to_use);

private:
    // Reads the file "file_name" and creates appropriate YDLdata-objects and pushes them in the "data" vector.
    void read_file();

    string file_name;

    // 2-Queued 1-Downloading 0-Finished
    map<YDLdata *, int> progress;
};


#endif