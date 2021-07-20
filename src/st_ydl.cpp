#include "st_ydl.hpp"
#include "ydl_data.hpp"

#include <fstream>
#include <iostream>

#include <boost/thread.hpp>

boost::mutex coutMutex;

using namespace std;

STydl::STydl(string _file)
: file_name(_file)
{
    read_file();
}

STydl::~STydl()
{
    for (int i = 0; i < data.size(); ++i)
        delete data[i];
}

void STydl::download_all()
{
    for (int i = 0; i < data.size(); ++i)
    {
        cout << *data[i] << endl;
        data[i]->download();
    }
}

void STydl::read_file()
{
    ifstream in_file;
    in_file.open(file_name);
    if (!in_file)
    {
        cerr << "Error:\n\tOpening " << file_name << " for reading" << endl;
        exit(EXIT_FAILURE);
    }

    YDLdata *new_YDLdata;
    string command;
    string path;

    // Create for every link an object and push it in to the "data"-vector.
    // "command" and "path" might be the same over multiple links that's why they are saved in variables.
    string line;
    while (getline(in_file, line))
    {
        // Ignore empty lines and do nothing if the line starts with a " " (space).
        if (line != "")
        {
            switch (line.at(0))
            {
            case '>':
                line.erase(0, 1);
                command = line;
                break;
            
            case '#':
                line.erase(0, 1);
                path = line;
                break;

            case 'h':
                if (!command.empty())
                    new_YDLdata = new YDLdata(path, line, command);
                else
                    new_YDLdata = new YDLdata(path, line);

                data.push_back(new_YDLdata);
                break;
            
            default:
                break;
            }
        }
    }    
}

int STydl::operator~() const
{
    return data.size();
}

void STydl::operator[](unsigned int i) const
{
    if (i > data.size() - 1)
        return;
    coutMutex.lock();
    cout << "Start downloading link [" << i + 1 << "] out of [" << data.size() << "]" << endl;
    coutMutex.unlock();

    data[i]->download();
    coutMutex.lock();
    cout << "\t-> Finished [" << i + 1 << "] out of [" << data.size() << "] links downloading." << endl;
    coutMutex.unlock();
}