#ifndef __ST_YDL_HPP__
#define __ST_YDL_HPP__

#include <string>
#include <vector>

using namespace std;

class YDLdata;

class STydl
{
public:
    STydl(string _file);
    ~STydl();

     
    // Downloads everything that was specified in the file (excluding commented out lines).
    void download_all();

    // Returns the number of Downloads to be executed.
    int operator~() const;
    // Downloads the i link.
    void operator[](unsigned int i) const;

private:
    // Reads the file "file_name" and creates appropriate YDLdata-objects and pushes them in the "data" vector.
    void read_file();

    string file_name;
    vector<YDLdata *> data;
};


#endif